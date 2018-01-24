import time

class Logger:
   def __init__(self, filename):
      self.filename = filename
      timestr = time.strftime('-%Y-%m-%d')
      filename_fmt = self.filename + timestr + '.log'
      self.f = open(filename_fmt, 'a')
      self.log('Logger started')

   def log(self, msg):
      logtime = time.strftime('%Y-%m-%d %H:%M:%S')
      msg_str = str(logtime + ' - ' + msg + '\n')
      self.f.write(msg_str)
      self.f.flush()

   def rotate(self):
      self.log('Rotating log')
      timestr = time.strftime('-%Y-%m-%d')
      filename_fmt = self.filename + timestr + '.log'
      self.f.close()
      self.f = open(filename_fmt, 'w')
      self.log('Log rotation finished')