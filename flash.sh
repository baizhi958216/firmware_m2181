#!/bin/bash
FastbootFiles=(abl dsp hyp modem tz xbl aop cpucp keymaster qupfw uefisecapp bluetooth devcfg featenabler logo shrm xbl_config)
echo -e "\n\n\n\n\n\n\t\t\tFlyme9.2.5.3A\n\n\t\t5秒后开始刷入，请勿挪动数据线或设备\n\n\nmeizu/meizu_18_CN/meizu18:11/RKQ1.210715.001/1646967620:user/release-keys\n\n\n\n\n"
sleep 5
for i in ${FastbootFiles[*]}
do
fastboot flash $i $i.img
done
