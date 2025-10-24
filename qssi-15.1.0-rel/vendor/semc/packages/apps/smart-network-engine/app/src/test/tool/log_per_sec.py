import numpy as np
import pandas as pd
import sys

args = sys.argv
if len(args) <= 1:
    print("Enter a file name as the argument.")
    exit(1)

# read csv
filename = sys.argv[1] # e.g. filename = './test_loop_predict_20220303065651577.csv'
df = pd.read_csv(filename, sep=',')

# resample 1sec
df.index = pd.DatetimeIndex(
    pd.to_datetime(df.timestamp, format="%Y/%m/%d %H:%M:%S")
)
df.index.name = "#time"
df_1sec = df.resample("1S").agg({"loopCount": np.max})

# calc diff
diff = df_1sec.loopCount.diff()
diff[0] = df_1sec.loopCount[0]

df_1sec['diff'] = diff.astype('int')

# write csv
outfile = './test_loop_predict_1sec.csv'
df_1sec.to_csv(outfile, header=True, index=True, sep=',')
