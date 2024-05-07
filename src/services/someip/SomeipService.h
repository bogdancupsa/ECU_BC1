#ifndef SOMEIP_SERVICE_H
#define SOMEIP_SERVICE_H

#include <vsomeip/vsomeip.hpp>

class SomeipService {
    public:
        SomeipService      ( void );
        void init          ( void );
        void start         ( void );
        void stop          ( void );
        void offer_service ( void );
        void on_message    ( const std::shared_ptr<vsomeip::message> &request );
    
    private:
        std::shared_ptr<vsomeip::application> app_;
};

#endif // SOMEIP_SERVICE_H