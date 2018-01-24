#!/bin/env python3

import time
from coind import *
from logger import *

TARGETTIME = int(5*61)
current_height = 1
blocktime_prev = 0
tot_trans = 0

coind = Coind()
log = Logger('checkpoints')


height = coind.getblockcount()
while(current_height <= height):
   blockhash = coind.getblockhash(current_height)
   if blocktime_prev is 0:
      prev_height = current_height - 1
      blockhash_prev = coind.getblockhash(prev_height)
      blockinfo_prev = coind.getblock(blockhash_prev)
      blocktine_prev = blockinfo_prev['time']
   blockinfo = coind.getblock(blockhash)
   blockage = int(blockinfo['time'] - blocktime_prev)
   num_tx = len(blockinfo['tx'])
   tot_trans = num_tx + tot_trans
   log_str = "%i\t%i seconds, %i transactions (culm. %i)" % (current_height, blockage, num_tx, tot_trans)
   log.log(log_str)
   blocktime_prev = blockinfo['time']
   current_height = current_height + 1