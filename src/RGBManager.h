#ifndef RGB_MANAGER_H
#define RGB_MANAGER_H

#define LED_MAX 255
#define LED_MIN 0

class RGBManager {
   public:
    RGBManager(int rPin, int gPin, int bPin, int fadeSpeed);
    void setR(int value);
    void setG(int value);
    void setB(int value);
    void turnOffLight();
    void setRGB(int r, int g, int b);
    void fadeToRGB(int r, int g, int b);
    void pulse();
    void rainbowAnimation();

    int CURRENT_R_VALUE;
    int CURRENT_G_VALUE;
    int CURRENT_B_VALUE;

   private:
    int R_PIN;
    int G_PIN;
    int B_PIN;
    int FADE_SPEED;

    int pulseSpeed = 2;
    bool pulsingUp = true;
    int topPulseValue = LED_MAX - pulseSpeed;
    int bottomPulseValue = 25;
};

#endif
