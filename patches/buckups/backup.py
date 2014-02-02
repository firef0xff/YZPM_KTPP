#!/usr/bin/env python

import sys;
import os;
from datetime import datetime


DB_USER = 'root';
DB_PASS = '';
DB_HOST = 'localhost';
act_bacup = False;
act_restore = False;
act_patch = False;
act_execute = False;
used_file = "";

def Help():
  print "--h -- this help";
  print;
  print "<Mysql connection params:>";
  print "-u -- server connection user";
  print "-p -- server connection password";
  print "-h -- server host";
  print;
  print "<Data base acton params:>";
  print "-B -- backup";
  print "-R -- restore backup";
  print "-P -- apply patch";
  print "-e -- execute script";
  print "-f -- use file";

  sys.exit(0);

def run_cmd( cmd ):
  dt = datetime.now()
  print str(dt) + "\t   CMD:", cmd
  sys.stdout.flush()
  r = os.system( cmd )
  if r != 0:
    raise Exception( "Error: \"%s\" While running \"%s\"" % ( str(r), cmd ) )
  return True;

def ParceArgv():
  global DB_USER;
  global DB_PASS;
  global DB_HOST;

  global act_bacup;
  global act_restore;
  global act_patch;
  global act_execute;
  global used_file;

  for i in xrange (len( sys.argv )):
    if sys.argv[i]=='-u':
      DB_USER = sys.argv[i+1];
    if sys.argv[i]=='-p':
      DB_PASS = sys.argv[i+1];
    if sys.argv[i]=='-h':
      DB_HOST = sys.argv[i+1];


    if sys.argv[i]=='-B':
      act_bacup = True;
    if sys.argv[i]=='-R':
      act_restore = True;
    if sys.argv[i]=='-P':
      act_patch = True;
    if sys.argv[i]=='-e':
      act_execute = True;
    if sys.argv[i]=='-f':
      used_file = sys.argv[i+1];
    if sys.argv[i]=='--help':
      Help();
      sys.exit(0);
  return None;


def main():
  ParceArgv();
  pwd = '';
  if len(DB_PASS):
    pwd = "-p"+DB_PASS;

  if act_bacup:
    file_name = "backup"+datetime.today().strftime('%y%m%d%H%M%S');
    run_cmd('mysqldump -u%s %s -h%s --opt -R -B administration billets catalogs constructions equipment instrum manufacture market oasu processed_list sklad technologic temporary_tables > %s'%(DB_USER,pwd,DB_HOST,file_name));
    run_cmd('gzip -9 %s'%file_name);
  elif act_restore:
    file_name = used_file[:len(used_file)-3];
    run_cmd('gzip -d -c %s > %s'%(used_file,file_name));
    run_cmd('mysql -u%s %s -h%s < %s'%(DB_USER,pwd,DB_HOST,file_name));
    run_cmd('rm -f %s'%file_name);	
  elif act_patch:
    file_name = "patch"+datetime.today().strftime('%y%m%d%H%M%S');
    run_cmd('mysqldump -u%s %s -h%s --no-create-info --no-data --triggers --routines --events -B administration billets catalogs constructions equipment instrum manufacture market oasu processed_list sklad technologic temporary_tables > %s'%(DB_USER,pwd,DB_HOST,file_name));
    run_cmd('gzip -9 %s'%file_name);
  elif act_execute:
    run_cmd('mysql -u%s %s -h%s < %s'%(DB_USER,pwd,DB_HOST,used_file));

if __name__ == "__main__":
  main();

















