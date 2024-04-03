#include "vars.h"
#include "vars_can_bus.h"
#include <iostream>

typedef void (*eventFunction)(info_msg &msg);

#define PICO_ID CanManager::canbus_vars.node_address
#define HUB CanManager::hub

class CanManager {
    private:
        static MCP2515 canController;
        static unsigned char* interruptPin;
        static volatile bool dataAvailable;
        static std::map<my_type, eventFunction> _actionMap;
        //struct can_frame canMsgTx, canMsgRx;
        //static void ISR_wrapper();
    public:
        static canBus_vars canbus_vars;
        static unsigned char hub;
        static bool hubFlag;
        static bool hubFound;
        //Can Manager
        static CanManager *instance; // Static instance pointer for ISR access
        static void     begin(char bitrate);
        static void     flashIDsetup();
        static void     canInterrupt();
        static void     setUpFiltersAndMasks ();
        static bool     receiveMessage(struct can_frame &msg);
        static bool     data_available();

        static void     canBusRotine();
        static void     canBUS_to_actions_rotine();
        static info_msg extract_message(can_frame *frame);
        static void     enqueue_message(unsigned char sender, my_type type, unsigned char *message, std::size_t msg_size);
        static void     serial_and_actions_rotine(void);
        static void     checkHub();
        static void     printID();
        static void     wake_up_grid();
        static bool     check_wake_up_condition();
        static void     acknoledge(char type);


        //Can Actions
        static void     createMap(void);
        static void     ackAction(info_msg &msg);
        static void     setReferenceAction(info_msg &msg);
        static void     setDutyCycleAction(info_msg &msg);
        static void     setOccupancyAction(info_msg &msg);
        static void     getDutyCycleAction(info_msg &msg);
        static void     getReferenceAction(info_msg &msg);
        static void     getIluminanceAction(info_msg &msg);
        static void     getOccupancyAction(info_msg &msg);
        static void     serialGetReferenceAction(info_msg &msg);
        static void     serialGetDutyCycleAction(info_msg &msg);
        static void     serialGetIluminanceAction(info_msg &msg);
        static void     serialGetOccupancyAction(info_msg &msg);
        static void     foundHubAction(info_msg &msg);
        static void     WakeUpAction(info_msg &msg);
        static void     ackInternalAction(info_msg &msg);
        static void     measureNOlightAction(info_msg &msg);
        static void     measurelightAction(info_msg &msg);
        static void     NotifyThisLightAction(info_msg &msg);
        static void     EndGainsAction(info_msg &msg);
        static void     loopUntilACK(int nrOfAcknoledge, unsigned char sender, my_type type, unsigned char *message, std::size_t msg_size);

};