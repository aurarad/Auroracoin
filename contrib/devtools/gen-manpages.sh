#!/usr/bin/env bash

export LC_ALL=C
TOPDIR=${TOPDIR:-$(git rev-parse --show-toplevel)}
BUILDDIR=${BUILDDIR:-$TOPDIR}

BINDIR=${BINDIR:-$BUILDDIR/src}
MANDIR=${MANDIR:-$TOPDIR/doc/man}

AURORACOIND=${AURORACOIND:-$BINDIR/auroracoind}
AURORACOINCLI=${AURORACOINCLI:-$BINDIR/auroracoin-cli}
AURORACOINTX=${AURORACOINTX:-$BINDIR/auroracoin-tx}
WALLET_TOOL=${WALLET_TOOL:-$BINDIR/auroracoin-wallet}
AURORACOINQT=${AURORACOINQT:-$BINDIR/qt/auroracoin-qt}

[ ! -x $AURORACOIND ] && echo "$AURORACOIND not found or not executable." && exit 1

# The autodetected version git tag can screw up manpage output a little bit
read -r -a AURVER <<< "$($AURORACOINCLI --version | head -n1 | awk -F'[ -]' '{ print $6, $7 }')"

# Create a footer file with copyright content.
# This gets autodetected fine for auroracoind if --version-string is not set,
# but has different outcomes for auroracoin-qt and auroracoin-cli.
echo "[COPYRIGHT]" > footer.h2m
$AURORACOIND --version | sed -n '1!p' >> footer.h2m

for cmd in $AURORACOIND $AURORACOINCLI $AURORACOINTX $WALLET_TOOL $AURORACOINQT; do
  cmdname="${cmd##*/}"
  help2man -N --version-string=${AURVER[0]} --include=footer.h2m -o ${MANDIR}/${cmdname}.1 ${cmd}
  sed -i "s/\\\-${AURVER[1]}//g" ${MANDIR}/${cmdname}.1
done

rm -f footer.h2m
