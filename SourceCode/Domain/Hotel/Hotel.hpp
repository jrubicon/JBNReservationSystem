#pragma once

#include <any>
#include <memory>
#include <string>
#include <vector>
#include <map>

#include "Domain/Hotel/HotelHandler.hpp"
#include "TechnicalServices/Logging/LoggerHandler.hpp"
#include "TechnicalServices/Logging/SimpleLogger.hpp"

namespace Domain::Hotel
{

  class HotelBase : public Domain::Hotel::HotelHandler
  {
  public:
    std::any addCostHotel(const std::vector<std::string> &args);
    std::any pay(const std::vector<std::string> &args);
    std::string checkoutHotel(const std::string number);
    std::string printAllRooms(std::string onlyavail);
    std::any reserveHotelRoom(const std::vector<std::string> &args);
    std::any unassignHotelRoom(const std::vector<std::string> &args);
    std::string assignHotelRoom(const std::string name, const std::string number);
    std::any askAvailableRoom(const std::vector<std::string> &args);
    double getPrice(std::string name);

    std::any executeCommand(const std::string &command, const std::vector<std::string> &args) override;

    HotelBase();
    ~HotelBase() noexcept override;

  protected:
  public:
    std::vector<std::vector<std::string>> roomInfo;
    std::unique_ptr<TechnicalServices::Logging::LoggerHandler> _loggerPtr;

    // convenience reference object enabling standard insertion syntax
    // This line must be physically after the definition of _loggerPtr
    TechnicalServices::Logging::LoggerHandler &_logger = *_loggerPtr;
    typedef std::any (HotelBase::*hotel_method)(const std::vector<std::string> &);
    using DispatchTable = std::map<std::string, hotel_method>;
    friend class Policy;
    DispatchTable _commandDispatch;
    std::map<std::string, double> pricing;
  };

} // namespace Domain::Hotel
