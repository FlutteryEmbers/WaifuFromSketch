modified from https://github.com/w-xuefeng/drawing

./ngrok http --subdomain drawstick 8080
./ngrok http --subdomain drawstickserver 9080

debug:
vue:
Error: ENOSPC: System limit for number of file watchers reached, watch '/home/wushili/Desktop/myStudy/WaifuFromSketch/public':
    echo fs.inotify.max_user_watches=524288 | sudo tee -a /etc/sysctl.conf && sudo sysctl -p
