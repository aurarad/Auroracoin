from bitcoinrpc.authproxy import AuthServiceProxy, JSONRPCException

class Coind:
   def __init__(self):
      # connect to the local coin daemon.
      self.access = AuthServiceProxy("http://%s:%s@127.0.0.1:12341"%('RPCuser', 'RPCpassword'))

   def getblockhash(self, idx):
      b_hash = self.access.getblockhash(idx)
      return(b_hash)

   def getblock(self, b_hash):
      block = self.access.getblock(b_hash)
      #{ u'merkleroot': u'74a2d1db8db7dc5e65d3d6f2058a6f1b5e893ddaf87c4c98d1a008e406b9beae', 
      #    u'nonce': 122400, 
      #    u'previousblockhash': u'6850dc01c014a262018fe2e29c299fc33dfe6d47fe5ef2f7cfa5f51f10bc61b3', 
      #    u'hash': u'642b7b504b315dd12683eb132e9a536958a89c03638ebc7582ef4d50893f0b89', 
      #    u'version': 2, 
      #    u'tx': [
      #        u'46eb85610e8260a5eeccdfb14bf393b83ff704ccaca08e2dc639c2ebd9cdff57', 
      #        u'dd28e708147c66b2ebaa23bfcce436afddfcdd1a268867465389c8c6d114cf82'
      #        ], 
      #    u'height': 176058, 
      #    u'difficulty': Decimal('587.97880435'), 
      #    u'nextblockhash': u'530761664af30cc6e119cef47222ff179982cdc6e5f1fd70d06bb72bafde649c', 
      #    u'confirmations': 7, 
      #    u'time': 1419937013, 
      #    u'bits': u'1b6f7546', 
      #    u'size': 1227
      #    }
      return(block)

   def gettransaction(self, t_hash):
      try:
         trans = self.access.gettransaction(t_hash)
      except:
         return(False)
      return(trans)

   def getblockcount(self):
      return(self.access.getblockcount())

