#ifndef _MAIN_H_
#define _MAIN_H_


#ifdef __cplusplus
extern "C" {
#endif    
    void app_main(void);
    void DisplayForecast();
    void DisplayText(int x, int y, String text);
    void DisplayWXicon(int x, int y, String IconName);
    bool obtain_forecast (String forecast_type);
    bool showWeather_astronomy(String* currCondString);
    bool showWeather_forecast(String* currCondString);
    int StartWiFi(const char* ssid, const char* password);
    void clear_screen();
    void SetupTime();
    void UpdateTime();
#ifdef __cplusplus    
}
#endif

#endif // _MAIN_H_
