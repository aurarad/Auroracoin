// Copyright (c) 2009-2019 The Bitcoin Core developers
// Copyright (c) 2014-2019 The DigiByte Core developers
// Copyright (c) 2014-2019 The Auroracoin Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef AURORACOIN_QT_TEST_RPCNESTEDTESTS_H
#define AURORACOIN_QT_TEST_RPCNESTEDTESTS_H

#include <QObject>
#include <QTest>

class RPCNestedTests : public QObject
{
    Q_OBJECT

    private Q_SLOTS:
    void rpcNestedTests();
};

#endif // AURORACOIN_QT_TEST_RPCNESTEDTESTS_H
