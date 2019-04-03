#include <iostream>
#include <iomanip>
#include <RTIMULib.h>
#include <memory>
#include <cstdint>

int main(int argc, char *argv[])
{
    int sampleCount = 0;
    int sampleRate = 0;
    uint64_t rateTimer;
    uint64_t displayTimer;
    uint64_t now;
    
    std::shared_ptr<RTIMUSettings> settings(new RTIMUSettings("RTIMULib"));
    std::shared_ptr<RTIMU> imu(RTIMU::createIMU(settings.get()));

    std::cout << std::endl;

    
    if ((imu == NULL) || (imu->IMUType() == RTIMU_TYPE_NULL)) {
        std::cerr << "No IMU found. Quitting." << std::endl;
        return 1;
    }

    // override any settings before IMUInit

    imu->IMUInit();

    // change fusion parameters here

    imu->setSlerpPower(0.02);
    imu->setGyroEnable(true);
    imu->setAccelEnable(true);
    imu->setCompassEnable(true);

    rateTimer = displayTimer = RTMath::currentUSecsSinceEpoch();

    std::cout << std::endl << std::endl << std::endl << std::endl << std::endl;

    while (1) {
        usleep(imu->IMUGetPollInterval() * 1000);

        while (imu->IMURead()) {
            RTIMU_DATA imuData = imu->getIMUData();
            sampleCount++;
            now = RTMath::currentUSecsSinceEpoch();
            std::cout << "\x1b" "[4A" << std::flush; // escape sequence, move cursor 4 lines up            
            std::cout << "Sample rate " << std::to_string(sampleRate) << "\r\n"
                //                << RTMath::displayDegrees("Gyro", imuData.fusionPose) << "\r\n"
                << std::setprecision(4)
                << "Gyro:    x:" << imuData.gyro.x() << ", y:" << imuData.gyro.y() << ", z:" << imuData.gyro.z() << "\r\n"
                << "Accel:   x:" <<  imuData.accel.x() << ",    \ty:" << imuData.accel.y() << ",    \tz:" << imuData.accel.z() << "\r\n"
                << "Compass: x:" << imuData.compass.x() << ",    \ty:" << imuData.compass.y() << ",    \tz:" << imuData.compass.z() << "\r\n"
                << std::flush;
            
            displayTimer = now;

            if ((now - rateTimer) > 1000000) {
                sampleRate = sampleCount;
                sampleCount = 0;
                rateTimer = now;
            }
        }
    }
}
