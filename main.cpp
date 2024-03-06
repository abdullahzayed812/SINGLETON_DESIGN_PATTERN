#include <iostream>
#include <vector>

class ConfigurationManager {
 private:
  std::string configurationPath;
  std::vector<std::string> servicesApis;
  std::string awsServiceUrl;
  // Other heavy data
  bool isLoaded = false;

  ConfigurationManager(std::string configurationPath) : configurationPath(configurationPath) {}

  static ConfigurationManager* ptrConfigurationManager;

 public:
  static ConfigurationManager* createInstance(const std::string& configs) {
    if (ConfigurationManager::ptrConfigurationManager == nullptr) {
      std::cout << "Creating a new configuration manager.\n";
      ConfigurationManager::ptrConfigurationManager = new ConfigurationManager(configs);
    }

    return ConfigurationManager::ptrConfigurationManager;
  }

  static void freeInstance() {
    if (ConfigurationManager::ptrConfigurationManager != nullptr) {
      delete ConfigurationManager::ptrConfigurationManager;
      ConfigurationManager::ptrConfigurationManager = nullptr;
    } else {
      std::cout << "Instance freed already.\n";
    }
  }

  void load() {
    if (this->isLoaded) {
      return;
    }

    // some heavy load
    std::cout << "Lazy loading\n";  // what is lazy loading? Google
    this->servicesApis.push_back("10.20.30.40");
    this->servicesApis.push_back("10.20.30.41");
    this->servicesApis.push_back("10.20.30.42");
    this->awsServiceUrl = "https://dynamodb.us-west-2.amazonaws.com";  // what is Amazon AWS?
    this->isLoaded = true;
  }

  std::string getAwsServicesUrl() {
    this->load();
    return this->awsServiceUrl;
  }
};

ConfigurationManager* ConfigurationManager::ptrConfigurationManager = nullptr;

void f1() {
  ConfigurationManager* mgr = ConfigurationManager::createInstance("/home/moustafa/conf_info.txt");
  std::cout << mgr->getAwsServicesUrl() << "\n";
}

void f2() {
  ConfigurationManager* mgr = ConfigurationManager::createInstance("/home/moustafa/conf_info.txt");
  std::cout << mgr->getAwsServicesUrl() << "\n";
}

int main() {
  f1();
  f2();

  // If we forgot to free, it will be memory leak!
  // We need more elegant solutions!
  ConfigurationManager::freeInstance();

  return 0;
}