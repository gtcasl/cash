#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import os
import subprocess
import multiprocessing
import re
import math

multi_context = False

DCE = 0
PIP = 0
CFO = 0
CSE = 0
BRO = 0
RPO = 0
PCX = 0

Before = 0
After = 0

BeforeM = 0
AfterM = 0

def analyze(logfile):

	global multi_context
	global DCE
        global PIP
        global CFO
	global CSE
        global BRO
	global RPO 
	global PCX
	global Before
	global After
	global BeforeM
	global AfterM

	with open(logfile, 'r') as fp:
		for line in fp:	
			if line.startswith('create merged context'):
				multi_context = True
				continue
			match = re.search('deleted (\d+) (\w+) nodes', line)			
			if match:
				token = match.group(2)
				if token == 'DCE':
					DCE += int(match.group(1))
				elif token == 'CSE':
					CSE += int(match.group(1))
				elif token == 'PIP':
					PIP += int(match.group(1))
				elif token == 'PCX':
					PCX += int(match.group(1))
				elif token == 'CFO':
					CFO += int(match.group(1))
				elif token == 'BRO':
					BRO += int(match.group(1))
				elif token == 'RPO':
					RPO += int(match.group(1))
				else:
					raise Exception("Invalid token!")
				continue
			match = re.search('Before optimization: (\d+)', line)			
			if match:
				if multi_context:
					BeforeM += int(match.group(1))
				else:
					Before += int(match.group(1))
				continue
			match = re.search('After optimization: (\d+)', line)			
			if match:
				if multi_context:
					AfterM += int(match.group(1))
				else:
					After += int(match.group(1))
				continue

	if multi_context:
		print("Before: %d" % (Before - (After - BeforeM)))
	else:
		print("Before: %d" % Before)
	print("DCE total: %d" % DCE)
	print("PIP total: %d" % PIP)
	print("CFO total: %d" % CFO)
        print("CSE total: %d" % CSE)
       	print("BRO total: %d" % BRO)
	print("RPO total: %d" % RPO)
	print("PCX total: %d" % PCX)
	if multi_context:
		print("After: %d" % AfterM)
	else:
		print("After: %d" % After)

analyze(sys.argv[1])
	
