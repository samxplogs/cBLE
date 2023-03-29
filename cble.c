#include <flipper/flipper.h>
#include <flipper/screen.h>
#include <flipper/ble.h>

// BLE scanning callback
void ble_scan_callback(ble_gap_evt_adv_report_t *report, void *context) {
    int *devices_count = (int *)context;
    (*devices_count)++;
}

int main(void) {
    // Initialize Flipper Zero
    flipper_init();

    // Initialize screen
    screen_init();
    screen_clear();
    screen_print("Scanning BLE devices...");

    // Initialize BLE
    ble_init();

    int devices_count = 0;

    // Set up scanning parameters
    ble_scan_parameters_t scan_params = {
        .interval = 0x00A0,
        .window = 0x0050,
        .filter_policy = BLE_SCAN_FILTER_ALLOW_ALL,
        .active = 1,
        .timeout = 10, // Scan for 10 seconds
        .callback = ble_scan_callback,
        .context = &devices_count,
    };

    // Start scanning for BLE devices
    ble_scan_start(&scan_params);

    // Wait for the scan to complete
    delay_ms(scan_params.timeout * 1000);

    // Print the number of devices found
    screen_clear();
    screen_print("BLE devices found:");
    screen_printf("\n\n%d", devices_count);

    // Deinitialize
    ble_deinit();
    screen_deinit();
    flipper_deinit();

    return 0;
}