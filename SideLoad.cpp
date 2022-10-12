#include <iostream>
#include <array>
#include <filesystem>
#include <vector>
#include <algorithm>

class FlashHelper
{
private:
  std::string partationName;
  std::string imageName;
  std::string command;

public:
  void SetPartationName(std::string &p_name)
  {
    partationName = p_name;
  }
  void SetImagePath(std::string &i_name)
  {
    imageName = i_name;
  }
  void FlashToPartation()
  {
    command = "fastboot flash " + partationName + " " + imageName;
    std::cout << command << std::endl;
    system(command.c_str());
  }
};

std::string GetDeviceConnection()
{
  std::string command("fastboot devices");
  std::array<char, 128> buffer;
  FILE *pipe = popen(command.c_str(), "r");
  std::string result;
  while (fgets(buffer.data(), 128, pipe) != NULL)
  {
    result += buffer.data();
  }
  std::cout<<"检测到设备: "<<result.substr(0,result.length()-10)<<std::endl;
  return result;
}

int main(void)
{
  std::vector<std::string> images = {
      "abl.img", "aop.img", "bluetooth.img", "cpucp.img", "devcfg.img",
      "dsp.img", "featenabler.img", "hyp.img", "keymaster.img", "logo.img",
      "modem.img", "qupfw.img", "shrm.img", "tz.img", "uefisecapp.img",
      "xbl_config.img", "xbl.img"};
  if (GetDeviceConnection() != "")
  {
    std::cout << "设备已连接" << std::endl;
    FlashHelper *fh = new FlashHelper();
    for (const auto &file : std::filesystem::directory_iterator("./"))
    {
      std::string OriginFilePath = file.path();
      std::vector<std::string>::iterator iterator = std::find(images.begin(), images.end(), OriginFilePath.substr(2));
      if (iterator != images.end())
      {
        std::string filePath = OriginFilePath.substr(2);
        std::string partationName = OriginFilePath.substr(2, OriginFilePath.length() - 6);
        fh->SetPartationName(partationName);
        fh->SetImagePath(filePath);
        fh->FlashToPartation();
      }
    }
  }
  else
  {
    std::cout << "请先通过USB连接你的设备!!!" << std::endl;
  }
}
