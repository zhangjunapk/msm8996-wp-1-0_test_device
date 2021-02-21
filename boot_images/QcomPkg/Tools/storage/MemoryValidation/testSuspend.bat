echo "adb shell ls -l /data/test/"
adb shell ls -l /data/test/

echo "adb -s 202084 push SuspendResumeWrite.sh /data/"
adb -s 202084 push SuspendResumeWrite.sh /data/

echo "adb -s 202084 shell sh /data/SuspendResumeWrite.sh 5 1000 1000"
adb -s 202084 shell sh /data/SuspendResumeWrite.sh 2 1000 1000


