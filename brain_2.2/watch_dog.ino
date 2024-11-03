
esp_task_wdt_config_t wdt_config = {
    .timeout_ms = WDT_TIMEOUT*1000,  // Use the defined macro for timeout
    .trigger_panic = true       // Optional: Set to true if you want the WDT to trigger a panic on timeout
};


void init_watchdog(){  
  esp_task_wdt_init(&wdt_config);     //enable panic so ESP32 restarts
  esp_task_wdt_add(NULL);                   //add current thread to WDT watch  
}