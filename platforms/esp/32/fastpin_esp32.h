#pragma once

FASTLED_NAMESPACE_BEGIN

struct FASTLED_ESP_IO {
  volatile uint32_t _GPO;
  volatile uint32_t _GPOS;
  volatile uint32_t _GPOC;
};

#define _GPB0 (*(FASTLED_ESP_IO*)(0x3ff44000))
#define _GPB1 (*(FASTLED_ESP_IO*)(0x3ff44010))
#define OUTPUT_PIN_LIMIT 34


template<uint8_t PIN, uint32_t MASK> class _ESPPIN {

public:
  typedef volatile uint32_t * port_ptr_t;
  typedef uint32_t port_t;

  inline static void setOutput() { pinMode(PIN, OUTPUT); }
  inline static void setInput() { pinMode(PIN, INPUT); }

  // inline static void hi() __attribute__ ((always_inline)) { if(PIN < 32) { _GPB0._GPOS = MASK; } else if (PIN < OUTPUT_PIN_LIMIT){ _GPB1._GPOS = MASK; } }
  inline static void hi() __attribute__ ((always_inline)) { gpio_set_level((gpio_num_t)PIN, HIGH); }

  // inline static void lo() __attribute__ ((always_inline)) { if(PIN < 32) { _GPB0._GPOC = MASK; } else if (PIN < OUTPUT_PIN_LIMIT){ _GPB1._GPOC = MASK; } }
  inline static void lo() __attribute__ ((always_inline)) { gpio_set_level((gpio_num_t)PIN, LOW); }
  // inline static void set(register port_t val) __attribute__ ((always_inline)) { if(PIN < 32) { _GPB0._GPO = val; } else if (PIN < OUTPUT_PIN_LIMIT){ _GPB1._GPO = val; }}
  inline static void set(register port_t val) __attribute__ ((always_inline)) { gpio_set_level((gpio_num_t)PIN, val); }

  inline static void strobe() __attribute__ ((always_inline)) { toggle(); toggle(); }

  inline static void toggle() __attribute__ ((always_inline)) { if(PIN < 32) { _GPB0._GPO ^= MASK; } else if (PIN < OUTPUT_PIN_LIMIT){ _GPB1._GPO = MASK; } }

  inline static void hi(register port_ptr_t port) __attribute__ ((always_inline)) { hi(); }
  inline static void lo(register port_ptr_t port) __attribute__ ((always_inline)) { lo(); }
  inline static void fastset(register port_ptr_t port, register port_t val) __attribute__ ((always_inline)) { *port = val; }

  inline static port_t hival() __attribute__ ((always_inline)) { if (PIN<OUTPUT_PIN_LIMIT) { return 0x004 | MASK;  }  }
  inline static port_t loval() __attribute__ ((always_inline)) { if (PIN<OUTPUT_PIN_LIMIT) { return 0x004 & ~MASK; } }
  inline static port_ptr_t port() __attribute__ ((always_inline)) { if(PIN<32) { return &_GPB0._GPO; } else if(PIN < OUTPUT_PIN_LIMIT){ return &_GPB1._GPO; } }
  inline static port_ptr_t sport() __attribute__ ((always_inline)) { if (PIN<32)return &_GPB0._GPOS; else if(PIN<OUTPUT_PIN_LIMIT) return &_GPB1._GPOS; }
  inline static port_ptr_t cport() __attribute__ ((always_inline)) { if (PIN<32)return &_GPB0._GPOC; else if(PIN<OUTPUT_PIN_LIMIT) return &_GPB1._GPOC; }
  inline static port_t mask() __attribute__ ((always_inline)) { return MASK; }

  inline static bool isset() __attribute__ ((always_inline)) { return (0x004 & MASK); }
};

#define _DEFPIN_ESP32(PIN, REAL_PIN) template<> class FastPin<PIN> : public _ESPPIN<REAL_PIN, (1<<(REAL_PIN & 0xFF))> {};


#ifdef FASTLED_ESP32_RAW_PIN_ORDER
_DEFPIN_ESP32(0,0); _DEFPIN_ESP32(1,1); _DEFPIN_ESP32(2,2); _DEFPIN_ESP32(3,3);
_DEFPIN_ESP32(4,4); _DEFPIN_ESP32(5,5); _DEFPIN_ESP32(6,6); _DEFPIN_ESP32(7,7);
_DEFPIN_ESP32(8,8); _DEFPIN_ESP32(9,9); _DEFPIN_ESP32(10,10);
_DEFPIN_ESP32(11,11); _DEFPIN_ESP32(12,12); _DEFPIN_ESP32(13,13);
_DEFPIN_ESP32(14,14); _DEFPIN_ESP32(15,15); _DEFPIN_ESP32(16,16);
_DEFPIN_ESP32(17,17); _DEFPIN_ESP32(18,18); _DEFPIN_ESP32(19,19);
_DEFPIN_ESP32(20,20); _DEFPIN_ESP32(21,21); _DEFPIN_ESP32(22,22);
_DEFPIN_ESP32(23,23); _DEFPIN_ESP32(24,24); _DEFPIN_ESP32(25,25);
_DEFPIN_ESP32(26,26); _DEFPIN_ESP32(27,27); _DEFPIN_ESP32(28,28);
_DEFPIN_ESP32(29,29); _DEFPIN_ESP32(30,30); _DEFPIN_ESP32(31,31);
_DEFPIN_ESP32(32,32); _DEFPIN_ESP32(33,33);

#define PORTA_FIRST_PIN 32
// The rest of the pins - these are generally not available
// _DEFPIN_ESP32(11,6);
// _DEFPIN_ESP32(12,7); _DEFPIN_ESP32(13,8); _DEFPIN_ESP32(14,9); _DEFPIN_ESP32(15,10);
// _DEFPIN_ESP32(16,11);

#endif

#define HAS_HARDWARE_PIN_SUPPORT

#define FASTLED_NAMESPACE_END
