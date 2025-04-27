#define JOYSTICK_SIZE 64

const uint8_t hidReportDescriptor[] = {
  0x05, 0x01,        // USAGE_PAGE (Generic Desktop)
  0x09, 0x04,        // USAGE (Joystick)
  0xa1, 0x01,        // COLLECTION (Application)

  // Steering Axis (X)
  0xA1, 0x00,        //   COLLECTION (Physical)
  0x09, 0x30,        //     USAGE (X)
  0x15, 0x00,        //     LOGICAL_MINIMUM (0)
  0x26, 0xFF, 0x03,  //     LOGICAL_MAXIMUM (1023)
  0x75, 0x10,        //     REPORT_SIZE (16)
  0x95, 0x01,        //     REPORT_COUNT (1)
  0x81, 0x02,        //     INPUT (Data,Var,Abs)
  0xC0,              //   END_COLLECTION

  // Raw Force Feedback Packet Receiving (via HID Output report)
  0x06, 0x00, 0xFF,  // USAGE_PAGE (Vendor Defined)
  0x09, 0x01,        // USAGE (Vendor Usage 1)
  0xA1, 0x01,        // COLLECTION (Application)
  0x15, 0x00,        //   LOGICAL_MINIMUM (0)
  0x26, 0xFF, 0x00,  //   LOGICAL_MAXIMUM (255)
  0x75, 0x08,        //   REPORT_SIZE (8)
  0x95, JOYSTICK_SIZE, // REPORT_COUNT (64)
  0x91, 0x02,        //   OUTPUT (Data,Var,Abs)
  0xC0,              // END_COLLECTION

  0xC0               // END_COLLECTION
};
