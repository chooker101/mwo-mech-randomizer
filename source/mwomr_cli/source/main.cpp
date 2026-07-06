#include <iostream>
#include <curl/curl.h>
#include "mwomr_api/MWOMechEncoder.hpp"

//using namespace mwomr_cli;

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
    size_t totalSize = size * nmemb;
    userp->append((char*)contents, totalSize);
    return totalSize;
}

int main(int argc, char** argv) {
    mwomr_api::ItemData erSmallLaser = mwomr_api::ItemData();
    erSmallLaser.mItemID = "kB";
    erSmallLaser.mItemType = mwomr_api::ItemType::movable;

    mwomr_api::ComponentData centerTorso = mwomr_api::ComponentData();
    centerTorso.mArmour = 17;
    centerTorso.mArmourBonus = 15;
    centerTorso.mRearArmour = 1;
    centerTorso.mRearArmourBonus = 0;
    centerTorso.mComponentType = mwomr_api::ComponentType::center_torso;

    mwomr_api::ComponentData leftTorso = mwomr_api::ComponentData();
    leftTorso.mArmour = 15;
    leftTorso.mArmourBonus = 12;
    leftTorso.mRearArmour = 1;
    leftTorso.mRearArmourBonus = 0;
    leftTorso.mComponentType = mwomr_api::ComponentType::left_torso;
    leftTorso.mOmniID = ":E7";

    mwomr_api::ComponentData rightTorso = mwomr_api::ComponentData();
    rightTorso.mArmour = 14;
    rightTorso.mArmourBonus = 12;
    rightTorso.mRearArmour = 1;
    rightTorso.mRearArmourBonus = 0;
    rightTorso.mComponentType = mwomr_api::ComponentType::right_torso;
    rightTorso.mOmniID = "<E7";

    mwomr_api::ComponentData leftArm = mwomr_api::ComponentData();
    leftArm.mArmour = 8;
    leftArm.mArmourBonus = 6;
    leftArm.mComponentType = mwomr_api::ComponentType::left_arm;
    leftArm.mOmniID = "9E7";
    leftArm.mItems.push_back(std::make_unique<mwomr_api::ItemData>(erSmallLaser));

    mwomr_api::ComponentData rightArm = mwomr_api::ComponentData();
    rightArm.mArmour = 7;
    rightArm.mArmourBonus = 6;
    rightArm.mComponentType = mwomr_api::ComponentType::right_arm;
    rightArm.mOmniID = "=E7";
    rightArm.mItems.push_back(std::make_unique<mwomr_api::ItemData>(erSmallLaser));

    mwomr_api::ComponentData leftLeg = mwomr_api::ComponentData();
    leftLeg.mArmour = 1;
    leftLeg.mArmourBonus = 0;
    leftLeg.mComponentType = mwomr_api::ComponentType::left_leg;
    leftLeg.mOmniID = ">E7";

    mwomr_api::ComponentData rightLeg = mwomr_api::ComponentData();
    rightLeg.mArmour = 1;
    rightLeg.mArmourBonus = 0;
    rightLeg.mComponentType = mwomr_api::ComponentType::right_leg;
    rightLeg.mOmniID = "?E7";

    mwomr_api::ComponentData head = mwomr_api::ComponentData();
    head.mArmour = 1;
    head.mArmourBonus = 0;
    head.mComponentType = mwomr_api::ComponentType::head;
    head.mOmniID = "8E7";

    mwomr_api::MechData mechData = mwomr_api::MechData();
    mechData.mIdCode = "W2";
    mechData.mArmourType = static_cast<int>(mwomr_api::upgrades::clan::armour::ferro);
    mechData.mStructureType = static_cast<int>(mwomr_api::upgrades::clan::structure::endo);
    mechData.mHeatsinkType = static_cast<int>(mwomr_api::upgrades::clan::heatsink::double_hs);
    mechData.mGuidanceType = static_cast<int>(mwomr_api::upgrades::guidance::std);
    mechData.mOmniType = static_cast<int>(mwomr_api::upgrades::omni::has);

    mwomr_api::upgrades::omni_actuator ra_ac = mwomr_api::upgrades::omni_actuator();
    ra_ac.ha = mwomr_api::upgrades::actuator::no;
    ra_ac.laa = mwomr_api::upgrades::actuator::no;
    mwomr_api::upgrades::omni_actuator la_ac = mwomr_api::upgrades::omni_actuator();
    la_ac.ha = mwomr_api::upgrades::actuator::no;
    la_ac.laa = mwomr_api::upgrades::actuator::no;
    mechData.mOmniActuators.push_back(std::make_unique<mwomr_api::upgrades::omni_actuator>(ra_ac));
    mechData.mOmniActuators.push_back(std::make_unique<mwomr_api::upgrades::omni_actuator>(la_ac));

    mechData.mComponents.push_back(std::make_unique<mwomr_api::ComponentData>(std::move(centerTorso)));
    mechData.mComponents.push_back(std::make_unique<mwomr_api::ComponentData>(std::move(rightTorso)));
    mechData.mComponents.push_back(std::make_unique<mwomr_api::ComponentData>(std::move(leftTorso)));
    mechData.mComponents.push_back(std::make_unique<mwomr_api::ComponentData>(std::move(leftArm)));
    mechData.mComponents.push_back(std::make_unique<mwomr_api::ComponentData>(std::move(rightArm)));
    mechData.mComponents.push_back(std::make_unique<mwomr_api::ComponentData>(std::move(leftLeg)));
    mechData.mComponents.push_back(std::make_unique<mwomr_api::ComponentData>(std::move(rightLeg)));
    mechData.mComponents.push_back(std::make_unique<mwomr_api::ComponentData>(std::move(head)));

    mwomr_api::MWOMechEncoder mechEncoder = mwomr_api::MWOMechEncoder();

    std::string code = mechEncoder.GetEncodedMech(mechData);

    std::cout << "Mech Code: " << code << std::endl;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    CURL* curl = curl_easy_init();

    if (curl) {
        std::string response_string;
        struct curl_slist* headers = NULL;

        // 1. Set the target URL
        curl_easy_setopt(curl, CURLOPT_URL, "https://mwo.nav-alpha.com/api/items/");

        // 2. Set the HTTP headers for JSON
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, "Accept: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // 3. Define your JSON payload
        std::string json_data = R"({})";

        // 4. Configure the POST request and data
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_data.c_str());

        // 5. Set up the callback to save the server response
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);

        // 6. Perform the request
        CURLcode res = curl_easy_perform(curl);

        // 7. Check for errors and output the response
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }
        else {
            std::cout << "Response received:\n" << response_string << std::endl;
        }

        // 8. Clean up resources
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    
    return 0;
}