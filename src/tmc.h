#ifndef TMC_H_
#define TMC_H_

#include <map>
#include <vector>

#include "rdsstring.h"

namespace redsea {
namespace tmc {

enum eDirection {
  DIR_POSITIVE, DIR_NEGATIVE
};
enum eEventNature {
  EVENT_INFO, EVENT_FORECAST
};
enum eEventDirectionality {
  DIR_SINGLE, DIR_BOTH
};
enum eEventUrgency {
  URGENCY_NONE, URGENCY_U, URGENCY_X
};
enum eDurationType {
  DURATION_DYNAMIC, DURATION_LASTING
};
enum eQuantifierType {
  Q_SMALL_NUMBER, Q_NUMBER, Q_LESS_THAN_METRES, Q_PERCENT, Q_UPTO_KMH,
  Q_UPTO_TIME, Q_DEG_CELSIUS, Q_TIME, Q_TONNES, Q_METRES, Q_UPTO_MILLIMETRES,
  Q_MHZ, Q_KHZ
};

class Event {
  public:
    Event();
    Event(std::string, std::string, uint16_t, uint16_t, uint16_t, uint16_t,
        uint16_t, uint16_t, bool);
    std::string description;
    std::string description_with_quantifier;
    uint16_t nature;
    uint16_t quantifier_type;
    uint16_t duration_type;
    uint16_t directionality;
    uint16_t urgency;
    uint16_t update_class;
    bool allows_quantifier;

};

Event getEvent(uint16_t code);
void loadEventData();

struct MessagePart {
  MessagePart() {};
  MessagePart(bool _is_received, std::vector<uint16_t> _data) :
    is_received(_is_received), data(_data) {};
  bool is_received;
  std::vector<uint16_t> data;
};

class TMC {
  public:
    TMC();
    void systemGroup(uint16_t message);
    void userGroup(uint16_t x, uint16_t y, uint16_t z);

  private:
    void newMessage(bool,std::vector<MessagePart>);

    bool is_initialized_;
    bool is_encrypted_;
    bool has_encid_;
    uint16_t ltn_;
    uint16_t sid_;
    uint16_t encid_;
    uint16_t ltnbe_;
    uint16_t current_ci_;
    std::vector<MessagePart> multi_group_buffer_;
    RDSString ps_;
};

class Message {
  public:
    Message(bool is_multi, bool is_loc_encrypted,
        std::vector<MessagePart> parts);
    std::string toString() const;
    void print() const;

  private:
    bool is_encrypted_;
    uint16_t duration_;
    uint16_t duration_type_;
    bool divertadv_;
    uint16_t direction_;
    uint16_t extent_;
    std::vector<uint16_t> events_;
    std::vector<uint16_t> supplementary_;
    std::map<uint16_t, uint16_t> quantifiers_;
    std::vector<uint16_t> diversion_;
    uint16_t location_;
    bool is_complete_;
    bool has_length_affected_;
    uint16_t length_affected_;
    bool has_time_until_;
    uint16_t time_until_;
    bool has_time_starts_;
    uint16_t time_starts_;
};

} // namespace tmc
} // namespace redsea
#endif // TMC_H_