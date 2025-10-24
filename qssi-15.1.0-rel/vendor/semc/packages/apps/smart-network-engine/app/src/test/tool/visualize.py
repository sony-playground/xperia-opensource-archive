#!python3.6.9
#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys

import matplotlib.pyplot as plt
import matplotlib.dates as mdates
import matplotlib.gridspec as gs
import matplotlib.figure
import numpy as np
import pandas as pd

def main(P, T):
    #T = 'TestDeployOnly.20220510130711'
    #T = 'TestEvaluationOnly.20220510140008'
    #T = 'TestLoopPredictManager.20220510142041'
    in_jstat = F'{P}/jstat_{T}.log'
    in_du = F'{P}/du_{T}.log'
    in_du2 = F'{P}/du2_{T}.log'
    in_docker = F'{P}/docker_stats_{T}.log'

    print(F"read: {in_jstat}")
    print(F"read: {in_du}")
    print(F"read: {in_du2}")
    print(F"read: {in_docker}")

    fig = plt.figure(figsize=(16.0, 20.0))

    spec = gs.GridSpec(ncols=1, nrows=5)

    ax1 = fig.add_subplot(spec[0])
    ax5 = fig.add_subplot(spec[1])
    ax5_2 = fig.add_subplot(spec[2])
    ax6 = fig.add_subplot(spec[3])
    ax7 = fig.add_subplot(spec[4])

    df = pd.read_csv(in_jstat, parse_dates=['timestamp'], sep='\s+', header=0, names=('timestamp','S0C','S1C','S0U','S1U','EC','EU','OC','OU','MC','MU','CCSC','CCSU','YGC','YGCT','FGC','FGCT','GCT'))
    #print(df)

    # (S0C + S1C + EC + OC + MC) / 1024
    df['alloc'] = (df['S0C'] + df['S1C'] + df['EC'] + df['OC'] + df['MC']) / 1024

    # (S0U + S1U + EU + OU) / 1024
    df['use'] = (df['S0C'] + df['S1U'] + df['EU'] + df['OU']) / 1024

    x1 = np.array(df.timestamp)
    y1 = np.array(df.alloc)
    y2 = np.array(df.use)

    ax1.plot(x1, y1, label='Heap size', color='orange', linewidth=3);
    ax1.plot(x1, y2, label='Used heap', color='blue');
    ax1.fill_between(x1, y1, y2=y2, color="orange", alpha=0.2)
    ax1.fill_between(x1, y2, color="lightblue", alpha=0.4)
    ax1.set_title('JVM - Heap')
    #labels = ax1.get_xticklabels()
    #plt.setp(labels, rotation=45, fontsize=10);
    ax1.set_ylabel('MiB')
    #ax1.xaxis.set_major_formatter(mdates.DateFormatter("%H:%M"))
    #ax1.xaxis.set_major_locator(mdates.SecondLocator(interval=60))
    #ax1.xaxis.set_minor_locator(mdates.SecondLocator(interval=30))
    ax1.grid()
    ax1.legend()

    df = pd.read_csv(in_du, parse_dates=['timestamp'], header=1, names=('timestamp','du'))
    #print(df)

    df['mb'] = df.du.div(1024*1024)
    x3 = np.array(df.timestamp)
    y7 = np.array(df.du)
    y8 = np.array(df.mb)
    #print(df)

    ax5.set_title('du - src/test/resources')
    ax5.set_ylabel('MiB')
    ax5.plot(x3, y8, label='MiB', color='green');
    ax5.grid()
    ax5.legend()

    df = pd.read_csv(in_du2, parse_dates=['timestamp'], header=1, names=('timestamp','du'))
    #print(df)

    df['mb'] = df.du.div(1024*1024)
    x3 = np.array(df.timestamp)
    y7 = np.array(df.du)
    y8 = np.array(df.mb)
    #print(df)

    ax5_2.set_title('du - src/test/resources2')
    ax5_2.set_ylabel('MiB')
    ax5_2.plot(x3, y8, label='MiB', color='green');
    ax5_2.grid()
    ax5_2.legend()

    df = pd.read_csv(in_docker, parse_dates=['timestamp'], header=1, names=('timestamp','NAME','CPU','MEM_USAGE','LIMIT','MEM','NET_INPUT', 'NET_OUTPUT','BLOCK_INPUT', 'BLOCK_OUTPUT'))
    #print(df)

    x4 = np.array(df.timestamp)
    y9 = np.array(df.CPU)
    y10 = np.array(df.MEM)
    y11 = np.array(df.MEM_USAGE)
    y12 = np.array(df.LIMIT)

    ax6.set_title('docker stats - CPU / MEM')
    ax6.set_ylabel('%')
    ax6.plot(x4, y9, label='CPU', color='blue');
    ax6.plot(x4, y10, label='MEM', color='magenta');
    ax6.grid()
    ax6.legend()

    ax7.set_title('docker stats - MEM_USAGE / LIMIT')
    ax7.set_ylabel('MiB')
    ax7.plot(x4, y12, label='LIMIT', color='orange');
    ax7.plot(x4, y11, label='MEM_USAGE', color='magenta');
    ax7.grid()
    ax7.legend()

    plt.suptitle(F"Graph - {T}", size=15)
    #plt.show()

    out_png = F"{P}/{T}.png"
    fig.savefig(out_png)
    print(F"write: {out_png}")

if __name__ == '__main__':
    P = sys.argv[1]
    T = sys.argv[2]
    main(P, T)

