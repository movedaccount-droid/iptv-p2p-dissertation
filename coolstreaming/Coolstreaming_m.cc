//
// Generated file, do not edit! Created by nedtool 5.4 from overlay/coolstreaming/../coolstreaming/Coolstreaming.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include "Coolstreaming_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp


// forward
template<typename T, typename A>
std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec);

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// operator<< for std::vector<T>
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

Register_Class(Membership)

Membership::Membership(const char *name, short kind) : ::BaseOverlayMessage(name,kind)
{
    this->uuid = 0;
    this->seq_num = 0;
    this->num_partner = 0;
    this->ttl = 0;
    this->bandwidth = 0;
    this->forwarded = false;
    this->entry = false;
}

Membership::Membership(const Membership& other) : ::BaseOverlayMessage(other)
{
    copy(other);
}

Membership::~Membership()
{
}

Membership& Membership::operator=(const Membership& other)
{
    if (this==&other) return *this;
    ::BaseOverlayMessage::operator=(other);
    copy(other);
    return *this;
}

void Membership::copy(const Membership& other)
{
    this->uuid = other.uuid;
    this->seq_num = other.seq_num;
    this->tad = other.tad;
    this->num_partner = other.num_partner;
    this->ttl = other.ttl;
    this->bandwidth = other.bandwidth;
    this->forwarded = other.forwarded;
    this->entry = other.entry;
}

void Membership::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::BaseOverlayMessage::parsimPack(b);
    doParsimPacking(b,this->uuid);
    doParsimPacking(b,this->seq_num);
    doParsimPacking(b,this->tad);
    doParsimPacking(b,this->num_partner);
    doParsimPacking(b,this->ttl);
    doParsimPacking(b,this->bandwidth);
    doParsimPacking(b,this->forwarded);
    doParsimPacking(b,this->entry);
}

void Membership::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::BaseOverlayMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->uuid);
    doParsimUnpacking(b,this->seq_num);
    doParsimUnpacking(b,this->tad);
    doParsimUnpacking(b,this->num_partner);
    doParsimUnpacking(b,this->ttl);
    doParsimUnpacking(b,this->bandwidth);
    doParsimUnpacking(b,this->forwarded);
    doParsimUnpacking(b,this->entry);
}

int Membership::getUuid() const
{
    return this->uuid;
}

void Membership::setUuid(int uuid)
{
    this->uuid = uuid;
}

int Membership::getSeq_num() const
{
    return this->seq_num;
}

void Membership::setSeq_num(int seq_num)
{
    this->seq_num = seq_num;
}

TransportAddress& Membership::getTad()
{
    return this->tad;
}

void Membership::setTad(const TransportAddress& tad)
{
    this->tad = tad;
}

int Membership::getNum_partner() const
{
    return this->num_partner;
}

void Membership::setNum_partner(int num_partner)
{
    this->num_partner = num_partner;
}

::omnetpp::simtime_t Membership::getTtl() const
{
    return this->ttl;
}

void Membership::setTtl(::omnetpp::simtime_t ttl)
{
    this->ttl = ttl;
}

double Membership::getBandwidth() const
{
    return this->bandwidth;
}

void Membership::setBandwidth(double bandwidth)
{
    this->bandwidth = bandwidth;
}

bool Membership::getForwarded() const
{
    return this->forwarded;
}

void Membership::setForwarded(bool forwarded)
{
    this->forwarded = forwarded;
}

bool Membership::getEntry() const
{
    return this->entry;
}

void Membership::setEntry(bool entry)
{
    this->entry = entry;
}

class MembershipDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    MembershipDescriptor();
    virtual ~MembershipDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(MembershipDescriptor)

MembershipDescriptor::MembershipDescriptor() : omnetpp::cClassDescriptor("Membership", "BaseOverlayMessage")
{
    propertynames = nullptr;
}

MembershipDescriptor::~MembershipDescriptor()
{
    delete[] propertynames;
}

bool MembershipDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Membership *>(obj)!=nullptr;
}

const char **MembershipDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *MembershipDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int MembershipDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 8+basedesc->getFieldCount() : 8;
}

unsigned int MembershipDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<8) ? fieldTypeFlags[field] : 0;
}

const char *MembershipDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "uuid",
        "seq_num",
        "tad",
        "num_partner",
        "ttl",
        "bandwidth",
        "forwarded",
        "entry",
    };
    return (field>=0 && field<8) ? fieldNames[field] : nullptr;
}

int MembershipDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='u' && strcmp(fieldName, "uuid")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "seq_num")==0) return base+1;
    if (fieldName[0]=='t' && strcmp(fieldName, "tad")==0) return base+2;
    if (fieldName[0]=='n' && strcmp(fieldName, "num_partner")==0) return base+3;
    if (fieldName[0]=='t' && strcmp(fieldName, "ttl")==0) return base+4;
    if (fieldName[0]=='b' && strcmp(fieldName, "bandwidth")==0) return base+5;
    if (fieldName[0]=='f' && strcmp(fieldName, "forwarded")==0) return base+6;
    if (fieldName[0]=='e' && strcmp(fieldName, "entry")==0) return base+7;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *MembershipDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
        "TransportAddress",
        "int",
        "simtime_t",
        "double",
        "bool",
        "bool",
    };
    return (field>=0 && field<8) ? fieldTypeStrings[field] : nullptr;
}

const char **MembershipDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *MembershipDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int MembershipDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    Membership *pp = (Membership *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *MembershipDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Membership *pp = (Membership *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string MembershipDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Membership *pp = (Membership *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getUuid());
        case 1: return long2string(pp->getSeq_num());
        case 2: {std::stringstream out; out << pp->getTad(); return out.str();}
        case 3: return long2string(pp->getNum_partner());
        case 4: return simtime2string(pp->getTtl());
        case 5: return double2string(pp->getBandwidth());
        case 6: return bool2string(pp->getForwarded());
        case 7: return bool2string(pp->getEntry());
        default: return "";
    }
}

bool MembershipDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    Membership *pp = (Membership *)object; (void)pp;
    switch (field) {
        case 0: pp->setUuid(string2long(value)); return true;
        case 1: pp->setSeq_num(string2long(value)); return true;
        case 3: pp->setNum_partner(string2long(value)); return true;
        case 4: pp->setTtl(string2simtime(value)); return true;
        case 5: pp->setBandwidth(string2double(value)); return true;
        case 6: pp->setForwarded(string2bool(value)); return true;
        case 7: pp->setEntry(string2bool(value)); return true;
        default: return false;
    }
}

const char *MembershipDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 2: return omnetpp::opp_typename(typeid(TransportAddress));
        default: return nullptr;
    };
}

void *MembershipDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    Membership *pp = (Membership *)object; (void)pp;
    switch (field) {
        case 2: return (void *)(&pp->getTad()); break;
        default: return nullptr;
    }
}

Register_Class(InviewCall)

InviewCall::InviewCall(const char *name, short kind) : ::BaseCallMessage(name,kind)
{
}

InviewCall::InviewCall(const InviewCall& other) : ::BaseCallMessage(other)
{
    copy(other);
}

InviewCall::~InviewCall()
{
}

InviewCall& InviewCall::operator=(const InviewCall& other)
{
    if (this==&other) return *this;
    ::BaseCallMessage::operator=(other);
    copy(other);
    return *this;
}

void InviewCall::copy(const InviewCall& other)
{
    this->destination = other.destination;
    this->accepting_node = other.accepting_node;
}

void InviewCall::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::BaseCallMessage::parsimPack(b);
    doParsimPacking(b,this->destination);
    doParsimPacking(b,this->accepting_node);
}

void InviewCall::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::BaseCallMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->destination);
    doParsimUnpacking(b,this->accepting_node);
}

TransportAddress& InviewCall::getDestination()
{
    return this->destination;
}

void InviewCall::setDestination(const TransportAddress& destination)
{
    this->destination = destination;
}

TransportAddress& InviewCall::getAccepting_node()
{
    return this->accepting_node;
}

void InviewCall::setAccepting_node(const TransportAddress& accepting_node)
{
    this->accepting_node = accepting_node;
}

class InviewCallDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    InviewCallDescriptor();
    virtual ~InviewCallDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(InviewCallDescriptor)

InviewCallDescriptor::InviewCallDescriptor() : omnetpp::cClassDescriptor("InviewCall", "BaseCallMessage")
{
    propertynames = nullptr;
}

InviewCallDescriptor::~InviewCallDescriptor()
{
    delete[] propertynames;
}

bool InviewCallDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<InviewCall *>(obj)!=nullptr;
}

const char **InviewCallDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *InviewCallDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int InviewCallDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount() : 2;
}

unsigned int InviewCallDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *InviewCallDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "destination",
        "accepting_node",
    };
    return (field>=0 && field<2) ? fieldNames[field] : nullptr;
}

int InviewCallDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='d' && strcmp(fieldName, "destination")==0) return base+0;
    if (fieldName[0]=='a' && strcmp(fieldName, "accepting_node")==0) return base+1;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *InviewCallDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "TransportAddress",
        "TransportAddress",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : nullptr;
}

const char **InviewCallDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *InviewCallDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int InviewCallDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    InviewCall *pp = (InviewCall *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *InviewCallDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    InviewCall *pp = (InviewCall *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string InviewCallDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    InviewCall *pp = (InviewCall *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getDestination(); return out.str();}
        case 1: {std::stringstream out; out << pp->getAccepting_node(); return out.str();}
        default: return "";
    }
}

bool InviewCallDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    InviewCall *pp = (InviewCall *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *InviewCallDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0: return omnetpp::opp_typename(typeid(TransportAddress));
        case 1: return omnetpp::opp_typename(typeid(TransportAddress));
        default: return nullptr;
    };
}

void *InviewCallDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    InviewCall *pp = (InviewCall *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getDestination()); break;
        case 1: return (void *)(&pp->getAccepting_node()); break;
        default: return nullptr;
    }
}

Register_Class(InviewResponse)

InviewResponse::InviewResponse(const char *name, short kind) : ::BaseResponseMessage(name,kind)
{
}

InviewResponse::InviewResponse(const InviewResponse& other) : ::BaseResponseMessage(other)
{
    copy(other);
}

InviewResponse::~InviewResponse()
{
}

InviewResponse& InviewResponse::operator=(const InviewResponse& other)
{
    if (this==&other) return *this;
    ::BaseResponseMessage::operator=(other);
    copy(other);
    return *this;
}

void InviewResponse::copy(const InviewResponse& other)
{
}

void InviewResponse::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::BaseResponseMessage::parsimPack(b);
}

void InviewResponse::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::BaseResponseMessage::parsimUnpack(b);
}

class InviewResponseDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    InviewResponseDescriptor();
    virtual ~InviewResponseDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(InviewResponseDescriptor)

InviewResponseDescriptor::InviewResponseDescriptor() : omnetpp::cClassDescriptor("InviewResponse", "BaseResponseMessage")
{
    propertynames = nullptr;
}

InviewResponseDescriptor::~InviewResponseDescriptor()
{
    delete[] propertynames;
}

bool InviewResponseDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<InviewResponse *>(obj)!=nullptr;
}

const char **InviewResponseDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *InviewResponseDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int InviewResponseDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount() : 0;
}

unsigned int InviewResponseDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    return 0;
}

const char *InviewResponseDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

int InviewResponseDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *InviewResponseDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

const char **InviewResponseDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *InviewResponseDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int InviewResponseDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    InviewResponse *pp = (InviewResponse *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *InviewResponseDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    InviewResponse *pp = (InviewResponse *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string InviewResponseDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    InviewResponse *pp = (InviewResponse *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool InviewResponseDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    InviewResponse *pp = (InviewResponse *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *InviewResponseDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

void *InviewResponseDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    InviewResponse *pp = (InviewResponse *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(Unsubscription)

Unsubscription::Unsubscription(const char *name, short kind) : ::BaseOverlayMessage(name,kind)
{
    this->inview = false;
}

Unsubscription::Unsubscription(const Unsubscription& other) : ::BaseOverlayMessage(other)
{
    copy(other);
}

Unsubscription::~Unsubscription()
{
}

Unsubscription& Unsubscription::operator=(const Unsubscription& other)
{
    if (this==&other) return *this;
    ::BaseOverlayMessage::operator=(other);
    copy(other);
    return *this;
}

void Unsubscription::copy(const Unsubscription& other)
{
    this->leaving = other.leaving;
    this->replacement = other.replacement;
    this->inview = other.inview;
}

void Unsubscription::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::BaseOverlayMessage::parsimPack(b);
    doParsimPacking(b,this->leaving);
    doParsimPacking(b,this->replacement);
    doParsimPacking(b,this->inview);
}

void Unsubscription::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::BaseOverlayMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->leaving);
    doParsimUnpacking(b,this->replacement);
    doParsimUnpacking(b,this->inview);
}

TransportAddress& Unsubscription::getLeaving()
{
    return this->leaving;
}

void Unsubscription::setLeaving(const TransportAddress& leaving)
{
    this->leaving = leaving;
}

TransportAddress& Unsubscription::getReplacement()
{
    return this->replacement;
}

void Unsubscription::setReplacement(const TransportAddress& replacement)
{
    this->replacement = replacement;
}

bool Unsubscription::getInview() const
{
    return this->inview;
}

void Unsubscription::setInview(bool inview)
{
    this->inview = inview;
}

class UnsubscriptionDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    UnsubscriptionDescriptor();
    virtual ~UnsubscriptionDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(UnsubscriptionDescriptor)

UnsubscriptionDescriptor::UnsubscriptionDescriptor() : omnetpp::cClassDescriptor("Unsubscription", "BaseOverlayMessage")
{
    propertynames = nullptr;
}

UnsubscriptionDescriptor::~UnsubscriptionDescriptor()
{
    delete[] propertynames;
}

bool UnsubscriptionDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Unsubscription *>(obj)!=nullptr;
}

const char **UnsubscriptionDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *UnsubscriptionDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int UnsubscriptionDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount() : 3;
}

unsigned int UnsubscriptionDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *UnsubscriptionDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "leaving",
        "replacement",
        "inview",
    };
    return (field>=0 && field<3) ? fieldNames[field] : nullptr;
}

int UnsubscriptionDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='l' && strcmp(fieldName, "leaving")==0) return base+0;
    if (fieldName[0]=='r' && strcmp(fieldName, "replacement")==0) return base+1;
    if (fieldName[0]=='i' && strcmp(fieldName, "inview")==0) return base+2;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *UnsubscriptionDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "TransportAddress",
        "TransportAddress",
        "bool",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : nullptr;
}

const char **UnsubscriptionDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *UnsubscriptionDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int UnsubscriptionDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    Unsubscription *pp = (Unsubscription *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *UnsubscriptionDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Unsubscription *pp = (Unsubscription *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string UnsubscriptionDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Unsubscription *pp = (Unsubscription *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getLeaving(); return out.str();}
        case 1: {std::stringstream out; out << pp->getReplacement(); return out.str();}
        case 2: return bool2string(pp->getInview());
        default: return "";
    }
}

bool UnsubscriptionDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    Unsubscription *pp = (Unsubscription *)object; (void)pp;
    switch (field) {
        case 2: pp->setInview(string2bool(value)); return true;
        default: return false;
    }
}

const char *UnsubscriptionDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0: return omnetpp::opp_typename(typeid(TransportAddress));
        case 1: return omnetpp::opp_typename(typeid(TransportAddress));
        default: return nullptr;
    };
}

void *UnsubscriptionDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    Unsubscription *pp = (Unsubscription *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getLeaving()); break;
        case 1: return (void *)(&pp->getReplacement()); break;
        default: return nullptr;
    }
}

Register_Class(GossipedUnsubscription)

GossipedUnsubscription::GossipedUnsubscription(const char *name, short kind) : ::BaseOverlayMessage(name,kind)
{
}

GossipedUnsubscription::GossipedUnsubscription(const GossipedUnsubscription& other) : ::BaseOverlayMessage(other)
{
    copy(other);
}

GossipedUnsubscription::~GossipedUnsubscription()
{
}

GossipedUnsubscription& GossipedUnsubscription::operator=(const GossipedUnsubscription& other)
{
    if (this==&other) return *this;
    ::BaseOverlayMessage::operator=(other);
    copy(other);
    return *this;
}

void GossipedUnsubscription::copy(const GossipedUnsubscription& other)
{
    this->from = other.from;
    this->failing = other.failing;
}

void GossipedUnsubscription::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::BaseOverlayMessage::parsimPack(b);
    doParsimPacking(b,this->from);
    doParsimPacking(b,this->failing);
}

void GossipedUnsubscription::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::BaseOverlayMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->from);
    doParsimUnpacking(b,this->failing);
}

TransportAddress& GossipedUnsubscription::getFrom()
{
    return this->from;
}

void GossipedUnsubscription::setFrom(const TransportAddress& from)
{
    this->from = from;
}

TransportAddress& GossipedUnsubscription::getFailing()
{
    return this->failing;
}

void GossipedUnsubscription::setFailing(const TransportAddress& failing)
{
    this->failing = failing;
}

class GossipedUnsubscriptionDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    GossipedUnsubscriptionDescriptor();
    virtual ~GossipedUnsubscriptionDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(GossipedUnsubscriptionDescriptor)

GossipedUnsubscriptionDescriptor::GossipedUnsubscriptionDescriptor() : omnetpp::cClassDescriptor("GossipedUnsubscription", "BaseOverlayMessage")
{
    propertynames = nullptr;
}

GossipedUnsubscriptionDescriptor::~GossipedUnsubscriptionDescriptor()
{
    delete[] propertynames;
}

bool GossipedUnsubscriptionDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<GossipedUnsubscription *>(obj)!=nullptr;
}

const char **GossipedUnsubscriptionDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *GossipedUnsubscriptionDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int GossipedUnsubscriptionDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount() : 2;
}

unsigned int GossipedUnsubscriptionDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *GossipedUnsubscriptionDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "from",
        "failing",
    };
    return (field>=0 && field<2) ? fieldNames[field] : nullptr;
}

int GossipedUnsubscriptionDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='f' && strcmp(fieldName, "from")==0) return base+0;
    if (fieldName[0]=='f' && strcmp(fieldName, "failing")==0) return base+1;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *GossipedUnsubscriptionDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "TransportAddress",
        "TransportAddress",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : nullptr;
}

const char **GossipedUnsubscriptionDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *GossipedUnsubscriptionDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int GossipedUnsubscriptionDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    GossipedUnsubscription *pp = (GossipedUnsubscription *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *GossipedUnsubscriptionDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    GossipedUnsubscription *pp = (GossipedUnsubscription *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string GossipedUnsubscriptionDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    GossipedUnsubscription *pp = (GossipedUnsubscription *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getFrom(); return out.str();}
        case 1: {std::stringstream out; out << pp->getFailing(); return out.str();}
        default: return "";
    }
}

bool GossipedUnsubscriptionDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    GossipedUnsubscription *pp = (GossipedUnsubscription *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *GossipedUnsubscriptionDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0: return omnetpp::opp_typename(typeid(TransportAddress));
        case 1: return omnetpp::opp_typename(typeid(TransportAddress));
        default: return nullptr;
    };
}

void *GossipedUnsubscriptionDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    GossipedUnsubscription *pp = (GossipedUnsubscription *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getFrom()); break;
        case 1: return (void *)(&pp->getFailing()); break;
        default: return nullptr;
    }
}

Register_Class(Heartbeat)

Heartbeat::Heartbeat(const char *name, short kind) : ::BaseOverlayMessage(name,kind)
{
}

Heartbeat::Heartbeat(const Heartbeat& other) : ::BaseOverlayMessage(other)
{
    copy(other);
}

Heartbeat::~Heartbeat()
{
}

Heartbeat& Heartbeat::operator=(const Heartbeat& other)
{
    if (this==&other) return *this;
    ::BaseOverlayMessage::operator=(other);
    copy(other);
    return *this;
}

void Heartbeat::copy(const Heartbeat& other)
{
}

void Heartbeat::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::BaseOverlayMessage::parsimPack(b);
}

void Heartbeat::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::BaseOverlayMessage::parsimUnpack(b);
}

class HeartbeatDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    HeartbeatDescriptor();
    virtual ~HeartbeatDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(HeartbeatDescriptor)

HeartbeatDescriptor::HeartbeatDescriptor() : omnetpp::cClassDescriptor("Heartbeat", "BaseOverlayMessage")
{
    propertynames = nullptr;
}

HeartbeatDescriptor::~HeartbeatDescriptor()
{
    delete[] propertynames;
}

bool HeartbeatDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Heartbeat *>(obj)!=nullptr;
}

const char **HeartbeatDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *HeartbeatDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int HeartbeatDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount() : 0;
}

unsigned int HeartbeatDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    return 0;
}

const char *HeartbeatDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

int HeartbeatDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *HeartbeatDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

const char **HeartbeatDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *HeartbeatDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int HeartbeatDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    Heartbeat *pp = (Heartbeat *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *HeartbeatDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Heartbeat *pp = (Heartbeat *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string HeartbeatDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Heartbeat *pp = (Heartbeat *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool HeartbeatDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    Heartbeat *pp = (Heartbeat *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *HeartbeatDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

void *HeartbeatDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    Heartbeat *pp = (Heartbeat *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(GetDeputyCall)

GetDeputyCall::GetDeputyCall(const char *name, short kind) : ::BaseCallMessage(name,kind)
{
}

GetDeputyCall::GetDeputyCall(const GetDeputyCall& other) : ::BaseCallMessage(other)
{
    copy(other);
}

GetDeputyCall::~GetDeputyCall()
{
}

GetDeputyCall& GetDeputyCall::operator=(const GetDeputyCall& other)
{
    if (this==&other) return *this;
    ::BaseCallMessage::operator=(other);
    copy(other);
    return *this;
}

void GetDeputyCall::copy(const GetDeputyCall& other)
{
    this->dest = other.dest;
}

void GetDeputyCall::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::BaseCallMessage::parsimPack(b);
    doParsimPacking(b,this->dest);
}

void GetDeputyCall::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::BaseCallMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->dest);
}

TransportAddress& GetDeputyCall::getDest()
{
    return this->dest;
}

void GetDeputyCall::setDest(const TransportAddress& dest)
{
    this->dest = dest;
}

class GetDeputyCallDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    GetDeputyCallDescriptor();
    virtual ~GetDeputyCallDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(GetDeputyCallDescriptor)

GetDeputyCallDescriptor::GetDeputyCallDescriptor() : omnetpp::cClassDescriptor("GetDeputyCall", "BaseCallMessage")
{
    propertynames = nullptr;
}

GetDeputyCallDescriptor::~GetDeputyCallDescriptor()
{
    delete[] propertynames;
}

bool GetDeputyCallDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<GetDeputyCall *>(obj)!=nullptr;
}

const char **GetDeputyCallDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *GetDeputyCallDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int GetDeputyCallDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount() : 1;
}

unsigned int GetDeputyCallDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *GetDeputyCallDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "dest",
    };
    return (field>=0 && field<1) ? fieldNames[field] : nullptr;
}

int GetDeputyCallDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='d' && strcmp(fieldName, "dest")==0) return base+0;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *GetDeputyCallDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "TransportAddress",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : nullptr;
}

const char **GetDeputyCallDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *GetDeputyCallDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int GetDeputyCallDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    GetDeputyCall *pp = (GetDeputyCall *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *GetDeputyCallDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    GetDeputyCall *pp = (GetDeputyCall *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string GetDeputyCallDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    GetDeputyCall *pp = (GetDeputyCall *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getDest(); return out.str();}
        default: return "";
    }
}

bool GetDeputyCallDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    GetDeputyCall *pp = (GetDeputyCall *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *GetDeputyCallDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0: return omnetpp::opp_typename(typeid(TransportAddress));
        default: return nullptr;
    };
}

void *GetDeputyCallDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    GetDeputyCall *pp = (GetDeputyCall *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getDest()); break;
        default: return nullptr;
    }
}

Register_Class(GetDeputyResponse)

GetDeputyResponse::GetDeputyResponse(const char *name, short kind) : ::BaseResponseMessage(name,kind)
{
    this->block_index = 0;
}

GetDeputyResponse::GetDeputyResponse(const GetDeputyResponse& other) : ::BaseResponseMessage(other)
{
    copy(other);
}

GetDeputyResponse::~GetDeputyResponse()
{
}

GetDeputyResponse& GetDeputyResponse::operator=(const GetDeputyResponse& other)
{
    if (this==&other) return *this;
    ::BaseResponseMessage::operator=(other);
    copy(other);
    return *this;
}

void GetDeputyResponse::copy(const GetDeputyResponse& other)
{
    this->deputy = other.deputy;
    this->block_index = other.block_index;
}

void GetDeputyResponse::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::BaseResponseMessage::parsimPack(b);
    doParsimPacking(b,this->deputy);
    doParsimPacking(b,this->block_index);
}

void GetDeputyResponse::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::BaseResponseMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->deputy);
    doParsimUnpacking(b,this->block_index);
}

TransportAddress& GetDeputyResponse::getDeputy()
{
    return this->deputy;
}

void GetDeputyResponse::setDeputy(const TransportAddress& deputy)
{
    this->deputy = deputy;
}

int GetDeputyResponse::getBlock_index() const
{
    return this->block_index;
}

void GetDeputyResponse::setBlock_index(int block_index)
{
    this->block_index = block_index;
}

class GetDeputyResponseDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    GetDeputyResponseDescriptor();
    virtual ~GetDeputyResponseDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(GetDeputyResponseDescriptor)

GetDeputyResponseDescriptor::GetDeputyResponseDescriptor() : omnetpp::cClassDescriptor("GetDeputyResponse", "BaseResponseMessage")
{
    propertynames = nullptr;
}

GetDeputyResponseDescriptor::~GetDeputyResponseDescriptor()
{
    delete[] propertynames;
}

bool GetDeputyResponseDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<GetDeputyResponse *>(obj)!=nullptr;
}

const char **GetDeputyResponseDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *GetDeputyResponseDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int GetDeputyResponseDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount() : 2;
}

unsigned int GetDeputyResponseDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *GetDeputyResponseDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "deputy",
        "block_index",
    };
    return (field>=0 && field<2) ? fieldNames[field] : nullptr;
}

int GetDeputyResponseDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='d' && strcmp(fieldName, "deputy")==0) return base+0;
    if (fieldName[0]=='b' && strcmp(fieldName, "block_index")==0) return base+1;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *GetDeputyResponseDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "TransportAddress",
        "int",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : nullptr;
}

const char **GetDeputyResponseDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *GetDeputyResponseDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int GetDeputyResponseDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    GetDeputyResponse *pp = (GetDeputyResponse *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *GetDeputyResponseDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    GetDeputyResponse *pp = (GetDeputyResponse *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string GetDeputyResponseDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    GetDeputyResponse *pp = (GetDeputyResponse *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getDeputy(); return out.str();}
        case 1: return long2string(pp->getBlock_index());
        default: return "";
    }
}

bool GetDeputyResponseDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    GetDeputyResponse *pp = (GetDeputyResponse *)object; (void)pp;
    switch (field) {
        case 1: pp->setBlock_index(string2long(value)); return true;
        default: return false;
    }
}

const char *GetDeputyResponseDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0: return omnetpp::opp_typename(typeid(TransportAddress));
        default: return nullptr;
    };
}

void *GetDeputyResponseDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    GetDeputyResponse *pp = (GetDeputyResponse *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getDeputy()); break;
        default: return nullptr;
    }
}

Register_Class(GetCandidatePartnersCall)

GetCandidatePartnersCall::GetCandidatePartnersCall(const char *name, short kind) : ::BaseCallMessage(name,kind)
{
}

GetCandidatePartnersCall::GetCandidatePartnersCall(const GetCandidatePartnersCall& other) : ::BaseCallMessage(other)
{
    copy(other);
}

GetCandidatePartnersCall::~GetCandidatePartnersCall()
{
}

GetCandidatePartnersCall& GetCandidatePartnersCall::operator=(const GetCandidatePartnersCall& other)
{
    if (this==&other) return *this;
    ::BaseCallMessage::operator=(other);
    copy(other);
    return *this;
}

void GetCandidatePartnersCall::copy(const GetCandidatePartnersCall& other)
{
    this->from = other.from;
}

void GetCandidatePartnersCall::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::BaseCallMessage::parsimPack(b);
    doParsimPacking(b,this->from);
}

void GetCandidatePartnersCall::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::BaseCallMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->from);
}

TransportAddress& GetCandidatePartnersCall::getFrom()
{
    return this->from;
}

void GetCandidatePartnersCall::setFrom(const TransportAddress& from)
{
    this->from = from;
}

class GetCandidatePartnersCallDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    GetCandidatePartnersCallDescriptor();
    virtual ~GetCandidatePartnersCallDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(GetCandidatePartnersCallDescriptor)

GetCandidatePartnersCallDescriptor::GetCandidatePartnersCallDescriptor() : omnetpp::cClassDescriptor("GetCandidatePartnersCall", "BaseCallMessage")
{
    propertynames = nullptr;
}

GetCandidatePartnersCallDescriptor::~GetCandidatePartnersCallDescriptor()
{
    delete[] propertynames;
}

bool GetCandidatePartnersCallDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<GetCandidatePartnersCall *>(obj)!=nullptr;
}

const char **GetCandidatePartnersCallDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *GetCandidatePartnersCallDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int GetCandidatePartnersCallDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount() : 1;
}

unsigned int GetCandidatePartnersCallDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *GetCandidatePartnersCallDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "from",
    };
    return (field>=0 && field<1) ? fieldNames[field] : nullptr;
}

int GetCandidatePartnersCallDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='f' && strcmp(fieldName, "from")==0) return base+0;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *GetCandidatePartnersCallDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "TransportAddress",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : nullptr;
}

const char **GetCandidatePartnersCallDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *GetCandidatePartnersCallDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int GetCandidatePartnersCallDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    GetCandidatePartnersCall *pp = (GetCandidatePartnersCall *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *GetCandidatePartnersCallDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    GetCandidatePartnersCall *pp = (GetCandidatePartnersCall *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string GetCandidatePartnersCallDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    GetCandidatePartnersCall *pp = (GetCandidatePartnersCall *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getFrom(); return out.str();}
        default: return "";
    }
}

bool GetCandidatePartnersCallDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    GetCandidatePartnersCall *pp = (GetCandidatePartnersCall *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *GetCandidatePartnersCallDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0: return omnetpp::opp_typename(typeid(TransportAddress));
        default: return nullptr;
    };
}

void *GetCandidatePartnersCallDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    GetCandidatePartnersCall *pp = (GetCandidatePartnersCall *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getFrom()); break;
        default: return nullptr;
    }
}

Register_Class(GetCandidatePartnersResponse)

GetCandidatePartnersResponse::GetCandidatePartnersResponse(const char *name, short kind) : ::BaseResponseMessage(name,kind)
{
}

GetCandidatePartnersResponse::GetCandidatePartnersResponse(const GetCandidatePartnersResponse& other) : ::BaseResponseMessage(other)
{
    copy(other);
}

GetCandidatePartnersResponse::~GetCandidatePartnersResponse()
{
}

GetCandidatePartnersResponse& GetCandidatePartnersResponse::operator=(const GetCandidatePartnersResponse& other)
{
    if (this==&other) return *this;
    ::BaseResponseMessage::operator=(other);
    copy(other);
    return *this;
}

void GetCandidatePartnersResponse::copy(const GetCandidatePartnersResponse& other)
{
    this->candidates = other.candidates;
}

void GetCandidatePartnersResponse::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::BaseResponseMessage::parsimPack(b);
    doParsimPacking(b,this->candidates);
}

void GetCandidatePartnersResponse::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::BaseResponseMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->candidates);
}

BandwidthMap& GetCandidatePartnersResponse::getCandidates()
{
    return this->candidates;
}

void GetCandidatePartnersResponse::setCandidates(const BandwidthMap& candidates)
{
    this->candidates = candidates;
}

class GetCandidatePartnersResponseDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    GetCandidatePartnersResponseDescriptor();
    virtual ~GetCandidatePartnersResponseDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(GetCandidatePartnersResponseDescriptor)

GetCandidatePartnersResponseDescriptor::GetCandidatePartnersResponseDescriptor() : omnetpp::cClassDescriptor("GetCandidatePartnersResponse", "BaseResponseMessage")
{
    propertynames = nullptr;
}

GetCandidatePartnersResponseDescriptor::~GetCandidatePartnersResponseDescriptor()
{
    delete[] propertynames;
}

bool GetCandidatePartnersResponseDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<GetCandidatePartnersResponse *>(obj)!=nullptr;
}

const char **GetCandidatePartnersResponseDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *GetCandidatePartnersResponseDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int GetCandidatePartnersResponseDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount() : 1;
}

unsigned int GetCandidatePartnersResponseDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *GetCandidatePartnersResponseDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "candidates",
    };
    return (field>=0 && field<1) ? fieldNames[field] : nullptr;
}

int GetCandidatePartnersResponseDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='c' && strcmp(fieldName, "candidates")==0) return base+0;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *GetCandidatePartnersResponseDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "BandwidthMap",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : nullptr;
}

const char **GetCandidatePartnersResponseDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *GetCandidatePartnersResponseDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int GetCandidatePartnersResponseDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    GetCandidatePartnersResponse *pp = (GetCandidatePartnersResponse *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *GetCandidatePartnersResponseDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    GetCandidatePartnersResponse *pp = (GetCandidatePartnersResponse *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string GetCandidatePartnersResponseDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    GetCandidatePartnersResponse *pp = (GetCandidatePartnersResponse *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getCandidates(); return out.str();}
        default: return "";
    }
}

bool GetCandidatePartnersResponseDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    GetCandidatePartnersResponse *pp = (GetCandidatePartnersResponse *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *GetCandidatePartnersResponseDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0: return omnetpp::opp_typename(typeid(BandwidthMap));
        default: return nullptr;
    };
}

void *GetCandidatePartnersResponseDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    GetCandidatePartnersResponse *pp = (GetCandidatePartnersResponse *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getCandidates()); break;
        default: return nullptr;
    }
}

EXECUTE_ON_STARTUP(
    omnetpp::cEnum *e = omnetpp::cEnum::find("SplitResult");
    if (!e) omnetpp::enums.getInstance()->add(e = new omnetpp::cEnum("SplitResult"));
    e->insert(SUCCESS, "SUCCESS");
    e->insert(FAILED, "FAILED");
)

Register_Class(SplitCall)

SplitCall::SplitCall(const char *name, short kind) : ::BaseCallMessage(name,kind)
{
    this->uuid = 0;
}

SplitCall::SplitCall(const SplitCall& other) : ::BaseCallMessage(other)
{
    copy(other);
}

SplitCall::~SplitCall()
{
}

SplitCall& SplitCall::operator=(const SplitCall& other)
{
    if (this==&other) return *this;
    ::BaseCallMessage::operator=(other);
    copy(other);
    return *this;
}

void SplitCall::copy(const SplitCall& other)
{
    this->uuid = other.uuid;
    this->into = other.into;
}

void SplitCall::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::BaseCallMessage::parsimPack(b);
    doParsimPacking(b,this->uuid);
    doParsimPacking(b,this->into);
}

void SplitCall::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::BaseCallMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->uuid);
    doParsimUnpacking(b,this->into);
}

int SplitCall::getUuid() const
{
    return this->uuid;
}

void SplitCall::setUuid(int uuid)
{
    this->uuid = uuid;
}

TransportAddress& SplitCall::getInto()
{
    return this->into;
}

void SplitCall::setInto(const TransportAddress& into)
{
    this->into = into;
}

class SplitCallDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    SplitCallDescriptor();
    virtual ~SplitCallDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(SplitCallDescriptor)

SplitCallDescriptor::SplitCallDescriptor() : omnetpp::cClassDescriptor("SplitCall", "BaseCallMessage")
{
    propertynames = nullptr;
}

SplitCallDescriptor::~SplitCallDescriptor()
{
    delete[] propertynames;
}

bool SplitCallDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SplitCall *>(obj)!=nullptr;
}

const char **SplitCallDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *SplitCallDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int SplitCallDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount() : 2;
}

unsigned int SplitCallDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *SplitCallDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "uuid",
        "into",
    };
    return (field>=0 && field<2) ? fieldNames[field] : nullptr;
}

int SplitCallDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='u' && strcmp(fieldName, "uuid")==0) return base+0;
    if (fieldName[0]=='i' && strcmp(fieldName, "into")==0) return base+1;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *SplitCallDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "TransportAddress",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : nullptr;
}

const char **SplitCallDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *SplitCallDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int SplitCallDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    SplitCall *pp = (SplitCall *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *SplitCallDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    SplitCall *pp = (SplitCall *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SplitCallDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    SplitCall *pp = (SplitCall *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getUuid());
        case 1: {std::stringstream out; out << pp->getInto(); return out.str();}
        default: return "";
    }
}

bool SplitCallDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    SplitCall *pp = (SplitCall *)object; (void)pp;
    switch (field) {
        case 0: pp->setUuid(string2long(value)); return true;
        default: return false;
    }
}

const char *SplitCallDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 1: return omnetpp::opp_typename(typeid(TransportAddress));
        default: return nullptr;
    };
}

void *SplitCallDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    SplitCall *pp = (SplitCall *)object; (void)pp;
    switch (field) {
        case 1: return (void *)(&pp->getInto()); break;
        default: return nullptr;
    }
}

Register_Class(SplitResponse)

SplitResponse::SplitResponse(const char *name, short kind) : ::BaseResponseMessage(name,kind)
{
    this->result = 0;
}

SplitResponse::SplitResponse(const SplitResponse& other) : ::BaseResponseMessage(other)
{
    copy(other);
}

SplitResponse::~SplitResponse()
{
}

SplitResponse& SplitResponse::operator=(const SplitResponse& other)
{
    if (this==&other) return *this;
    ::BaseResponseMessage::operator=(other);
    copy(other);
    return *this;
}

void SplitResponse::copy(const SplitResponse& other)
{
    this->result = other.result;
    this->first_node = other.first_node;
    this->second_node = other.second_node;
}

void SplitResponse::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::BaseResponseMessage::parsimPack(b);
    doParsimPacking(b,this->result);
    doParsimPacking(b,this->first_node);
    doParsimPacking(b,this->second_node);
}

void SplitResponse::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::BaseResponseMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->result);
    doParsimUnpacking(b,this->first_node);
    doParsimUnpacking(b,this->second_node);
}

int SplitResponse::getResult() const
{
    return this->result;
}

void SplitResponse::setResult(int result)
{
    this->result = result;
}

TransportAddress& SplitResponse::getFirst_node()
{
    return this->first_node;
}

void SplitResponse::setFirst_node(const TransportAddress& first_node)
{
    this->first_node = first_node;
}

TransportAddress& SplitResponse::getSecond_node()
{
    return this->second_node;
}

void SplitResponse::setSecond_node(const TransportAddress& second_node)
{
    this->second_node = second_node;
}

class SplitResponseDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    SplitResponseDescriptor();
    virtual ~SplitResponseDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(SplitResponseDescriptor)

SplitResponseDescriptor::SplitResponseDescriptor() : omnetpp::cClassDescriptor("SplitResponse", "BaseResponseMessage")
{
    propertynames = nullptr;
}

SplitResponseDescriptor::~SplitResponseDescriptor()
{
    delete[] propertynames;
}

bool SplitResponseDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SplitResponse *>(obj)!=nullptr;
}

const char **SplitResponseDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *SplitResponseDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int SplitResponseDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount() : 3;
}

unsigned int SplitResponseDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *SplitResponseDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "result",
        "first_node",
        "second_node",
    };
    return (field>=0 && field<3) ? fieldNames[field] : nullptr;
}

int SplitResponseDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='r' && strcmp(fieldName, "result")==0) return base+0;
    if (fieldName[0]=='f' && strcmp(fieldName, "first_node")==0) return base+1;
    if (fieldName[0]=='s' && strcmp(fieldName, "second_node")==0) return base+2;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *SplitResponseDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "TransportAddress",
        "TransportAddress",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : nullptr;
}

const char **SplitResponseDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *SplitResponseDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "SplitResult";
            return nullptr;
        default: return nullptr;
    }
}

int SplitResponseDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    SplitResponse *pp = (SplitResponse *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *SplitResponseDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    SplitResponse *pp = (SplitResponse *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SplitResponseDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    SplitResponse *pp = (SplitResponse *)object; (void)pp;
    switch (field) {
        case 0: return enum2string(pp->getResult(), "SplitResult");
        case 1: {std::stringstream out; out << pp->getFirst_node(); return out.str();}
        case 2: {std::stringstream out; out << pp->getSecond_node(); return out.str();}
        default: return "";
    }
}

bool SplitResponseDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    SplitResponse *pp = (SplitResponse *)object; (void)pp;
    switch (field) {
        case 0: pp->setResult((SplitResult)string2enum(value, "SplitResult")); return true;
        default: return false;
    }
}

const char *SplitResponseDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 1: return omnetpp::opp_typename(typeid(TransportAddress));
        case 2: return omnetpp::opp_typename(typeid(TransportAddress));
        default: return nullptr;
    };
}

void *SplitResponseDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    SplitResponse *pp = (SplitResponse *)object; (void)pp;
    switch (field) {
        case 1: return (void *)(&pp->getFirst_node()); break;
        case 2: return (void *)(&pp->getSecond_node()); break;
        default: return nullptr;
    }
}

Register_Class(TrySplitCall)

TrySplitCall::TrySplitCall(const char *name, short kind) : ::BaseCallMessage(name,kind)
{
    this->uuid = 0;
}

TrySplitCall::TrySplitCall(const TrySplitCall& other) : ::BaseCallMessage(other)
{
    copy(other);
}

TrySplitCall::~TrySplitCall()
{
}

TrySplitCall& TrySplitCall::operator=(const TrySplitCall& other)
{
    if (this==&other) return *this;
    ::BaseCallMessage::operator=(other);
    copy(other);
    return *this;
}

void TrySplitCall::copy(const TrySplitCall& other)
{
    this->uuid = other.uuid;
    this->into = other.into;
    this->from = other.from;
}

void TrySplitCall::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::BaseCallMessage::parsimPack(b);
    doParsimPacking(b,this->uuid);
    doParsimPacking(b,this->into);
    doParsimPacking(b,this->from);
}

void TrySplitCall::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::BaseCallMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->uuid);
    doParsimUnpacking(b,this->into);
    doParsimUnpacking(b,this->from);
}

int TrySplitCall::getUuid() const
{
    return this->uuid;
}

void TrySplitCall::setUuid(int uuid)
{
    this->uuid = uuid;
}

TransportAddress& TrySplitCall::getInto()
{
    return this->into;
}

void TrySplitCall::setInto(const TransportAddress& into)
{
    this->into = into;
}

TransportAddress& TrySplitCall::getFrom()
{
    return this->from;
}

void TrySplitCall::setFrom(const TransportAddress& from)
{
    this->from = from;
}

class TrySplitCallDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    TrySplitCallDescriptor();
    virtual ~TrySplitCallDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(TrySplitCallDescriptor)

TrySplitCallDescriptor::TrySplitCallDescriptor() : omnetpp::cClassDescriptor("TrySplitCall", "BaseCallMessage")
{
    propertynames = nullptr;
}

TrySplitCallDescriptor::~TrySplitCallDescriptor()
{
    delete[] propertynames;
}

bool TrySplitCallDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<TrySplitCall *>(obj)!=nullptr;
}

const char **TrySplitCallDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *TrySplitCallDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int TrySplitCallDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount() : 3;
}

unsigned int TrySplitCallDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *TrySplitCallDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "uuid",
        "into",
        "from",
    };
    return (field>=0 && field<3) ? fieldNames[field] : nullptr;
}

int TrySplitCallDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='u' && strcmp(fieldName, "uuid")==0) return base+0;
    if (fieldName[0]=='i' && strcmp(fieldName, "into")==0) return base+1;
    if (fieldName[0]=='f' && strcmp(fieldName, "from")==0) return base+2;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *TrySplitCallDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "TransportAddress",
        "TransportAddress",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : nullptr;
}

const char **TrySplitCallDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *TrySplitCallDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int TrySplitCallDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    TrySplitCall *pp = (TrySplitCall *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *TrySplitCallDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    TrySplitCall *pp = (TrySplitCall *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string TrySplitCallDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    TrySplitCall *pp = (TrySplitCall *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getUuid());
        case 1: {std::stringstream out; out << pp->getInto(); return out.str();}
        case 2: {std::stringstream out; out << pp->getFrom(); return out.str();}
        default: return "";
    }
}

bool TrySplitCallDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    TrySplitCall *pp = (TrySplitCall *)object; (void)pp;
    switch (field) {
        case 0: pp->setUuid(string2long(value)); return true;
        default: return false;
    }
}

const char *TrySplitCallDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 1: return omnetpp::opp_typename(typeid(TransportAddress));
        case 2: return omnetpp::opp_typename(typeid(TransportAddress));
        default: return nullptr;
    };
}

void *TrySplitCallDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    TrySplitCall *pp = (TrySplitCall *)object; (void)pp;
    switch (field) {
        case 1: return (void *)(&pp->getInto()); break;
        case 2: return (void *)(&pp->getFrom()); break;
        default: return nullptr;
    }
}

Register_Class(TrySplitResponse)

TrySplitResponse::TrySplitResponse(const char *name, short kind) : ::BaseResponseMessage(name,kind)
{
    this->uuid = 0;
    this->result = 0;
}

TrySplitResponse::TrySplitResponse(const TrySplitResponse& other) : ::BaseResponseMessage(other)
{
    copy(other);
}

TrySplitResponse::~TrySplitResponse()
{
}

TrySplitResponse& TrySplitResponse::operator=(const TrySplitResponse& other)
{
    if (this==&other) return *this;
    ::BaseResponseMessage::operator=(other);
    copy(other);
    return *this;
}

void TrySplitResponse::copy(const TrySplitResponse& other)
{
    this->uuid = other.uuid;
    this->result = other.result;
    this->into = other.into;
    this->from = other.from;
}

void TrySplitResponse::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::BaseResponseMessage::parsimPack(b);
    doParsimPacking(b,this->uuid);
    doParsimPacking(b,this->result);
    doParsimPacking(b,this->into);
    doParsimPacking(b,this->from);
}

void TrySplitResponse::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::BaseResponseMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->uuid);
    doParsimUnpacking(b,this->result);
    doParsimUnpacking(b,this->into);
    doParsimUnpacking(b,this->from);
}

int TrySplitResponse::getUuid() const
{
    return this->uuid;
}

void TrySplitResponse::setUuid(int uuid)
{
    this->uuid = uuid;
}

int TrySplitResponse::getResult() const
{
    return this->result;
}

void TrySplitResponse::setResult(int result)
{
    this->result = result;
}

TransportAddress& TrySplitResponse::getInto()
{
    return this->into;
}

void TrySplitResponse::setInto(const TransportAddress& into)
{
    this->into = into;
}

TransportAddress& TrySplitResponse::getFrom()
{
    return this->from;
}

void TrySplitResponse::setFrom(const TransportAddress& from)
{
    this->from = from;
}

class TrySplitResponseDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    TrySplitResponseDescriptor();
    virtual ~TrySplitResponseDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(TrySplitResponseDescriptor)

TrySplitResponseDescriptor::TrySplitResponseDescriptor() : omnetpp::cClassDescriptor("TrySplitResponse", "BaseResponseMessage")
{
    propertynames = nullptr;
}

TrySplitResponseDescriptor::~TrySplitResponseDescriptor()
{
    delete[] propertynames;
}

bool TrySplitResponseDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<TrySplitResponse *>(obj)!=nullptr;
}

const char **TrySplitResponseDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *TrySplitResponseDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int TrySplitResponseDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 4+basedesc->getFieldCount() : 4;
}

unsigned int TrySplitResponseDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<4) ? fieldTypeFlags[field] : 0;
}

const char *TrySplitResponseDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "uuid",
        "result",
        "into",
        "from",
    };
    return (field>=0 && field<4) ? fieldNames[field] : nullptr;
}

int TrySplitResponseDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='u' && strcmp(fieldName, "uuid")==0) return base+0;
    if (fieldName[0]=='r' && strcmp(fieldName, "result")==0) return base+1;
    if (fieldName[0]=='i' && strcmp(fieldName, "into")==0) return base+2;
    if (fieldName[0]=='f' && strcmp(fieldName, "from")==0) return base+3;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *TrySplitResponseDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
        "TransportAddress",
        "TransportAddress",
    };
    return (field>=0 && field<4) ? fieldTypeStrings[field] : nullptr;
}

const char **TrySplitResponseDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 1: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *TrySplitResponseDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 1:
            if (!strcmp(propertyname,"enum")) return "SplitResult";
            return nullptr;
        default: return nullptr;
    }
}

int TrySplitResponseDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    TrySplitResponse *pp = (TrySplitResponse *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *TrySplitResponseDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    TrySplitResponse *pp = (TrySplitResponse *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string TrySplitResponseDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    TrySplitResponse *pp = (TrySplitResponse *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getUuid());
        case 1: return enum2string(pp->getResult(), "SplitResult");
        case 2: {std::stringstream out; out << pp->getInto(); return out.str();}
        case 3: {std::stringstream out; out << pp->getFrom(); return out.str();}
        default: return "";
    }
}

bool TrySplitResponseDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    TrySplitResponse *pp = (TrySplitResponse *)object; (void)pp;
    switch (field) {
        case 0: pp->setUuid(string2long(value)); return true;
        case 1: pp->setResult((SplitResult)string2enum(value, "SplitResult")); return true;
        default: return false;
    }
}

const char *TrySplitResponseDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 2: return omnetpp::opp_typename(typeid(TransportAddress));
        case 3: return omnetpp::opp_typename(typeid(TransportAddress));
        default: return nullptr;
    };
}

void *TrySplitResponseDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    TrySplitResponse *pp = (TrySplitResponse *)object; (void)pp;
    switch (field) {
        case 2: return (void *)(&pp->getInto()); break;
        case 3: return (void *)(&pp->getFrom()); break;
        default: return nullptr;
    }
}

Register_Class(Leave)

Leave::Leave(const char *name, short kind) : ::BaseOverlayMessage(name,kind)
{
}

Leave::Leave(const Leave& other) : ::BaseOverlayMessage(other)
{
    copy(other);
}

Leave::~Leave()
{
}

Leave& Leave::operator=(const Leave& other)
{
    if (this==&other) return *this;
    ::BaseOverlayMessage::operator=(other);
    copy(other);
    return *this;
}

void Leave::copy(const Leave& other)
{
}

void Leave::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::BaseOverlayMessage::parsimPack(b);
}

void Leave::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::BaseOverlayMessage::parsimUnpack(b);
}

class LeaveDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    LeaveDescriptor();
    virtual ~LeaveDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(LeaveDescriptor)

LeaveDescriptor::LeaveDescriptor() : omnetpp::cClassDescriptor("Leave", "BaseOverlayMessage")
{
    propertynames = nullptr;
}

LeaveDescriptor::~LeaveDescriptor()
{
    delete[] propertynames;
}

bool LeaveDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Leave *>(obj)!=nullptr;
}

const char **LeaveDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *LeaveDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int LeaveDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount() : 0;
}

unsigned int LeaveDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    return 0;
}

const char *LeaveDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

int LeaveDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *LeaveDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

const char **LeaveDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *LeaveDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int LeaveDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    Leave *pp = (Leave *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *LeaveDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Leave *pp = (Leave *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string LeaveDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Leave *pp = (Leave *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool LeaveDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    Leave *pp = (Leave *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *LeaveDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

void *LeaveDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    Leave *pp = (Leave *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(Panic)

Panic::Panic(const char *name, short kind) : ::BaseOverlayMessage(name,kind)
{
}

Panic::Panic(const Panic& other) : ::BaseOverlayMessage(other)
{
    copy(other);
}

Panic::~Panic()
{
}

Panic& Panic::operator=(const Panic& other)
{
    if (this==&other) return *this;
    ::BaseOverlayMessage::operator=(other);
    copy(other);
    return *this;
}

void Panic::copy(const Panic& other)
{
    this->panicking = other.panicking;
}

void Panic::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::BaseOverlayMessage::parsimPack(b);
    doParsimPacking(b,this->panicking);
}

void Panic::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::BaseOverlayMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->panicking);
}

TransportAddress& Panic::getPanicking()
{
    return this->panicking;
}

void Panic::setPanicking(const TransportAddress& panicking)
{
    this->panicking = panicking;
}

class PanicDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    PanicDescriptor();
    virtual ~PanicDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(PanicDescriptor)

PanicDescriptor::PanicDescriptor() : omnetpp::cClassDescriptor("Panic", "BaseOverlayMessage")
{
    propertynames = nullptr;
}

PanicDescriptor::~PanicDescriptor()
{
    delete[] propertynames;
}

bool PanicDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Panic *>(obj)!=nullptr;
}

const char **PanicDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *PanicDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int PanicDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount() : 1;
}

unsigned int PanicDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *PanicDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "panicking",
    };
    return (field>=0 && field<1) ? fieldNames[field] : nullptr;
}

int PanicDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='p' && strcmp(fieldName, "panicking")==0) return base+0;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *PanicDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "TransportAddress",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : nullptr;
}

const char **PanicDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *PanicDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int PanicDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    Panic *pp = (Panic *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *PanicDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Panic *pp = (Panic *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string PanicDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Panic *pp = (Panic *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getPanicking(); return out.str();}
        default: return "";
    }
}

bool PanicDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    Panic *pp = (Panic *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *PanicDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0: return omnetpp::opp_typename(typeid(TransportAddress));
        default: return nullptr;
    };
}

void *PanicDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    Panic *pp = (Panic *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getPanicking()); break;
        default: return nullptr;
    }
}

EXECUTE_ON_STARTUP(
    omnetpp::cEnum *e = omnetpp::cEnum::find("PanicSplitState");
    if (!e) omnetpp::enums.getInstance()->add(e = new omnetpp::cEnum("PanicSplitState"));
    e->insert(KNOWN, "KNOWN");
    e->insert(UNKNOWN, "UNKNOWN");
)

Register_Class(PanicSplit)

PanicSplit::PanicSplit(const char *name, short kind) : ::BaseOverlayMessage(name,kind)
{
    this->state = 0;
}

PanicSplit::PanicSplit(const PanicSplit& other) : ::BaseOverlayMessage(other)
{
    copy(other);
}

PanicSplit::~PanicSplit()
{
}

PanicSplit& PanicSplit::operator=(const PanicSplit& other)
{
    if (this==&other) return *this;
    ::BaseOverlayMessage::operator=(other);
    copy(other);
    return *this;
}

void PanicSplit::copy(const PanicSplit& other)
{
    this->state = other.state;
    this->into = other.into;
    this->from = other.from;
}

void PanicSplit::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::BaseOverlayMessage::parsimPack(b);
    doParsimPacking(b,this->state);
    doParsimPacking(b,this->into);
    doParsimPacking(b,this->from);
}

void PanicSplit::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::BaseOverlayMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->state);
    doParsimUnpacking(b,this->into);
    doParsimUnpacking(b,this->from);
}

int PanicSplit::getState() const
{
    return this->state;
}

void PanicSplit::setState(int state)
{
    this->state = state;
}

TransportAddress& PanicSplit::getInto()
{
    return this->into;
}

void PanicSplit::setInto(const TransportAddress& into)
{
    this->into = into;
}

TransportAddress& PanicSplit::getFrom()
{
    return this->from;
}

void PanicSplit::setFrom(const TransportAddress& from)
{
    this->from = from;
}

class PanicSplitDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    PanicSplitDescriptor();
    virtual ~PanicSplitDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(PanicSplitDescriptor)

PanicSplitDescriptor::PanicSplitDescriptor() : omnetpp::cClassDescriptor("PanicSplit", "BaseOverlayMessage")
{
    propertynames = nullptr;
}

PanicSplitDescriptor::~PanicSplitDescriptor()
{
    delete[] propertynames;
}

bool PanicSplitDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<PanicSplit *>(obj)!=nullptr;
}

const char **PanicSplitDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *PanicSplitDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int PanicSplitDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount() : 3;
}

unsigned int PanicSplitDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *PanicSplitDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "state",
        "into",
        "from",
    };
    return (field>=0 && field<3) ? fieldNames[field] : nullptr;
}

int PanicSplitDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "state")==0) return base+0;
    if (fieldName[0]=='i' && strcmp(fieldName, "into")==0) return base+1;
    if (fieldName[0]=='f' && strcmp(fieldName, "from")==0) return base+2;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *PanicSplitDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "TransportAddress",
        "TransportAddress",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : nullptr;
}

const char **PanicSplitDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *PanicSplitDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "PanicSplitState";
            return nullptr;
        default: return nullptr;
    }
}

int PanicSplitDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    PanicSplit *pp = (PanicSplit *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *PanicSplitDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    PanicSplit *pp = (PanicSplit *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string PanicSplitDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    PanicSplit *pp = (PanicSplit *)object; (void)pp;
    switch (field) {
        case 0: return enum2string(pp->getState(), "PanicSplitState");
        case 1: {std::stringstream out; out << pp->getInto(); return out.str();}
        case 2: {std::stringstream out; out << pp->getFrom(); return out.str();}
        default: return "";
    }
}

bool PanicSplitDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    PanicSplit *pp = (PanicSplit *)object; (void)pp;
    switch (field) {
        case 0: pp->setState((PanicSplitState)string2enum(value, "PanicSplitState")); return true;
        default: return false;
    }
}

const char *PanicSplitDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 1: return omnetpp::opp_typename(typeid(TransportAddress));
        case 2: return omnetpp::opp_typename(typeid(TransportAddress));
        default: return nullptr;
    };
}

void *PanicSplitDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    PanicSplit *pp = (PanicSplit *)object; (void)pp;
    switch (field) {
        case 1: return (void *)(&pp->getInto()); break;
        case 2: return (void *)(&pp->getFrom()); break;
        default: return nullptr;
    }
}

Register_Class(PanicSplitFound)

PanicSplitFound::PanicSplitFound(const char *name, short kind) : ::BaseOverlayMessage(name,kind)
{
}

PanicSplitFound::PanicSplitFound(const PanicSplitFound& other) : ::BaseOverlayMessage(other)
{
    copy(other);
}

PanicSplitFound::~PanicSplitFound()
{
}

PanicSplitFound& PanicSplitFound::operator=(const PanicSplitFound& other)
{
    if (this==&other) return *this;
    ::BaseOverlayMessage::operator=(other);
    copy(other);
    return *this;
}

void PanicSplitFound::copy(const PanicSplitFound& other)
{
    this->into = other.into;
    this->from = other.from;
}

void PanicSplitFound::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::BaseOverlayMessage::parsimPack(b);
    doParsimPacking(b,this->into);
    doParsimPacking(b,this->from);
}

void PanicSplitFound::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::BaseOverlayMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->into);
    doParsimUnpacking(b,this->from);
}

TransportAddress& PanicSplitFound::getInto()
{
    return this->into;
}

void PanicSplitFound::setInto(const TransportAddress& into)
{
    this->into = into;
}

TransportAddress& PanicSplitFound::getFrom()
{
    return this->from;
}

void PanicSplitFound::setFrom(const TransportAddress& from)
{
    this->from = from;
}

class PanicSplitFoundDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    PanicSplitFoundDescriptor();
    virtual ~PanicSplitFoundDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(PanicSplitFoundDescriptor)

PanicSplitFoundDescriptor::PanicSplitFoundDescriptor() : omnetpp::cClassDescriptor("PanicSplitFound", "BaseOverlayMessage")
{
    propertynames = nullptr;
}

PanicSplitFoundDescriptor::~PanicSplitFoundDescriptor()
{
    delete[] propertynames;
}

bool PanicSplitFoundDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<PanicSplitFound *>(obj)!=nullptr;
}

const char **PanicSplitFoundDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *PanicSplitFoundDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int PanicSplitFoundDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount() : 2;
}

unsigned int PanicSplitFoundDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *PanicSplitFoundDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "into",
        "from",
    };
    return (field>=0 && field<2) ? fieldNames[field] : nullptr;
}

int PanicSplitFoundDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='i' && strcmp(fieldName, "into")==0) return base+0;
    if (fieldName[0]=='f' && strcmp(fieldName, "from")==0) return base+1;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *PanicSplitFoundDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "TransportAddress",
        "TransportAddress",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : nullptr;
}

const char **PanicSplitFoundDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *PanicSplitFoundDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int PanicSplitFoundDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    PanicSplitFound *pp = (PanicSplitFound *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *PanicSplitFoundDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    PanicSplitFound *pp = (PanicSplitFound *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string PanicSplitFoundDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    PanicSplitFound *pp = (PanicSplitFound *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getInto(); return out.str();}
        case 1: {std::stringstream out; out << pp->getFrom(); return out.str();}
        default: return "";
    }
}

bool PanicSplitFoundDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    PanicSplitFound *pp = (PanicSplitFound *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *PanicSplitFoundDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0: return omnetpp::opp_typename(typeid(TransportAddress));
        case 1: return omnetpp::opp_typename(typeid(TransportAddress));
        default: return nullptr;
    };
}

void *PanicSplitFoundDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    PanicSplitFound *pp = (PanicSplitFound *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getInto()); break;
        case 1: return (void *)(&pp->getFrom()); break;
        default: return nullptr;
    }
}

Register_Class(Recover)

Recover::Recover(const char *name, short kind) : ::BaseOverlayMessage(name,kind)
{
}

Recover::Recover(const Recover& other) : ::BaseOverlayMessage(other)
{
    copy(other);
}

Recover::~Recover()
{
}

Recover& Recover::operator=(const Recover& other)
{
    if (this==&other) return *this;
    ::BaseOverlayMessage::operator=(other);
    copy(other);
    return *this;
}

void Recover::copy(const Recover& other)
{
    this->helper = other.helper;
}

void Recover::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::BaseOverlayMessage::parsimPack(b);
    doParsimPacking(b,this->helper);
}

void Recover::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::BaseOverlayMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->helper);
}

TransportAddress& Recover::getHelper()
{
    return this->helper;
}

void Recover::setHelper(const TransportAddress& helper)
{
    this->helper = helper;
}

class RecoverDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    RecoverDescriptor();
    virtual ~RecoverDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(RecoverDescriptor)

RecoverDescriptor::RecoverDescriptor() : omnetpp::cClassDescriptor("Recover", "BaseOverlayMessage")
{
    propertynames = nullptr;
}

RecoverDescriptor::~RecoverDescriptor()
{
    delete[] propertynames;
}

bool RecoverDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Recover *>(obj)!=nullptr;
}

const char **RecoverDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *RecoverDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int RecoverDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount() : 1;
}

unsigned int RecoverDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *RecoverDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "helper",
    };
    return (field>=0 && field<1) ? fieldNames[field] : nullptr;
}

int RecoverDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='h' && strcmp(fieldName, "helper")==0) return base+0;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *RecoverDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "TransportAddress",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : nullptr;
}

const char **RecoverDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *RecoverDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int RecoverDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    Recover *pp = (Recover *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *RecoverDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Recover *pp = (Recover *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RecoverDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Recover *pp = (Recover *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getHelper(); return out.str();}
        default: return "";
    }
}

bool RecoverDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    Recover *pp = (Recover *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *RecoverDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0: return omnetpp::opp_typename(typeid(TransportAddress));
        default: return nullptr;
    };
}

void *RecoverDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    Recover *pp = (Recover *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getHelper()); break;
        default: return nullptr;
    }
}

Register_Class(BufferMap)

BufferMap::BufferMap(const char *name, short kind) : ::BaseOverlayMessage(name,kind)
{
}

BufferMap::BufferMap(const BufferMap& other) : ::BaseOverlayMessage(other)
{
    copy(other);
}

BufferMap::~BufferMap()
{
}

BufferMap& BufferMap::operator=(const BufferMap& other)
{
    if (this==&other) return *this;
    ::BaseOverlayMessage::operator=(other);
    copy(other);
    return *this;
}

void BufferMap::copy(const BufferMap& other)
{
    this->from = other.from;
    this->associate = other.associate;
    this->buffer_map = other.buffer_map;
}

void BufferMap::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::BaseOverlayMessage::parsimPack(b);
    doParsimPacking(b,this->from);
    doParsimPacking(b,this->associate);
    doParsimPacking(b,this->buffer_map);
}

void BufferMap::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::BaseOverlayMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->from);
    doParsimUnpacking(b,this->associate);
    doParsimUnpacking(b,this->buffer_map);
}

TransportAddress& BufferMap::getFrom()
{
    return this->from;
}

void BufferMap::setFrom(const TransportAddress& from)
{
    this->from = from;
}

TransportAddress& BufferMap::getAssociate()
{
    return this->associate;
}

void BufferMap::setAssociate(const TransportAddress& associate)
{
    this->associate = associate;
}

BM& BufferMap::getBuffer_map()
{
    return this->buffer_map;
}

void BufferMap::setBuffer_map(const BM& buffer_map)
{
    this->buffer_map = buffer_map;
}

class BufferMapDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    BufferMapDescriptor();
    virtual ~BufferMapDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(BufferMapDescriptor)

BufferMapDescriptor::BufferMapDescriptor() : omnetpp::cClassDescriptor("BufferMap", "BaseOverlayMessage")
{
    propertynames = nullptr;
}

BufferMapDescriptor::~BufferMapDescriptor()
{
    delete[] propertynames;
}

bool BufferMapDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<BufferMap *>(obj)!=nullptr;
}

const char **BufferMapDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *BufferMapDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int BufferMapDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount() : 3;
}

unsigned int BufferMapDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *BufferMapDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "from",
        "associate",
        "buffer_map",
    };
    return (field>=0 && field<3) ? fieldNames[field] : nullptr;
}

int BufferMapDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='f' && strcmp(fieldName, "from")==0) return base+0;
    if (fieldName[0]=='a' && strcmp(fieldName, "associate")==0) return base+1;
    if (fieldName[0]=='b' && strcmp(fieldName, "buffer_map")==0) return base+2;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *BufferMapDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "TransportAddress",
        "TransportAddress",
        "BM",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : nullptr;
}

const char **BufferMapDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *BufferMapDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int BufferMapDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    BufferMap *pp = (BufferMap *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *BufferMapDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    BufferMap *pp = (BufferMap *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string BufferMapDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    BufferMap *pp = (BufferMap *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getFrom(); return out.str();}
        case 1: {std::stringstream out; out << pp->getAssociate(); return out.str();}
        case 2: {std::stringstream out; out << pp->getBuffer_map(); return out.str();}
        default: return "";
    }
}

bool BufferMapDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    BufferMap *pp = (BufferMap *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *BufferMapDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0: return omnetpp::opp_typename(typeid(TransportAddress));
        case 1: return omnetpp::opp_typename(typeid(TransportAddress));
        case 2: return omnetpp::opp_typename(typeid(BM));
        default: return nullptr;
    };
}

void *BufferMapDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    BufferMap *pp = (BufferMap *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getFrom()); break;
        case 1: return (void *)(&pp->getAssociate()); break;
        case 2: return (void *)(&pp->getBuffer_map()); break;
        default: return nullptr;
    }
}

Register_Class(BlockRequest)

BlockRequest::BlockRequest(const char *name, short kind) : ::BaseOverlayMessage(name,kind)
{
}

BlockRequest::BlockRequest(const BlockRequest& other) : ::BaseOverlayMessage(other)
{
    copy(other);
}

BlockRequest::~BlockRequest()
{
}

BlockRequest& BlockRequest::operator=(const BlockRequest& other)
{
    if (this==&other) return *this;
    ::BaseOverlayMessage::operator=(other);
    copy(other);
    return *this;
}

void BlockRequest::copy(const BlockRequest& other)
{
    this->from = other.from;
    this->blocks = other.blocks;
}

void BlockRequest::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::BaseOverlayMessage::parsimPack(b);
    doParsimPacking(b,this->from);
    doParsimPacking(b,this->blocks);
}

void BlockRequest::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::BaseOverlayMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->from);
    doParsimUnpacking(b,this->blocks);
}

TransportAddress& BlockRequest::getFrom()
{
    return this->from;
}

void BlockRequest::setFrom(const TransportAddress& from)
{
    this->from = from;
}

BM& BlockRequest::getBlocks()
{
    return this->blocks;
}

void BlockRequest::setBlocks(const BM& blocks)
{
    this->blocks = blocks;
}

class BlockRequestDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    BlockRequestDescriptor();
    virtual ~BlockRequestDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(BlockRequestDescriptor)

BlockRequestDescriptor::BlockRequestDescriptor() : omnetpp::cClassDescriptor("BlockRequest", "BaseOverlayMessage")
{
    propertynames = nullptr;
}

BlockRequestDescriptor::~BlockRequestDescriptor()
{
    delete[] propertynames;
}

bool BlockRequestDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<BlockRequest *>(obj)!=nullptr;
}

const char **BlockRequestDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *BlockRequestDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int BlockRequestDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount() : 2;
}

unsigned int BlockRequestDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *BlockRequestDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "from",
        "blocks",
    };
    return (field>=0 && field<2) ? fieldNames[field] : nullptr;
}

int BlockRequestDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='f' && strcmp(fieldName, "from")==0) return base+0;
    if (fieldName[0]=='b' && strcmp(fieldName, "blocks")==0) return base+1;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *BlockRequestDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "TransportAddress",
        "BM",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : nullptr;
}

const char **BlockRequestDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *BlockRequestDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int BlockRequestDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    BlockRequest *pp = (BlockRequest *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *BlockRequestDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    BlockRequest *pp = (BlockRequest *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string BlockRequestDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    BlockRequest *pp = (BlockRequest *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getFrom(); return out.str();}
        case 1: {std::stringstream out; out << pp->getBlocks(); return out.str();}
        default: return "";
    }
}

bool BlockRequestDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    BlockRequest *pp = (BlockRequest *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *BlockRequestDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0: return omnetpp::opp_typename(typeid(TransportAddress));
        case 1: return omnetpp::opp_typename(typeid(BM));
        default: return nullptr;
    };
}

void *BlockRequestDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    BlockRequest *pp = (BlockRequest *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getFrom()); break;
        case 1: return (void *)(&pp->getBlocks()); break;
        default: return nullptr;
    }
}

Register_Class(Block)

Block::Block(const char *name, short kind) : ::BaseOverlayMessage(name,kind)
{
    this->index = 0;
}

Block::Block(const Block& other) : ::BaseOverlayMessage(other)
{
    copy(other);
}

Block::~Block()
{
}

Block& Block::operator=(const Block& other)
{
    if (this==&other) return *this;
    ::BaseOverlayMessage::operator=(other);
    copy(other);
    return *this;
}

void Block::copy(const Block& other)
{
    this->index = other.index;
}

void Block::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::BaseOverlayMessage::parsimPack(b);
    doParsimPacking(b,this->index);
}

void Block::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::BaseOverlayMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->index);
}

int Block::getIndex() const
{
    return this->index;
}

void Block::setIndex(int index)
{
    this->index = index;
}

class BlockDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    BlockDescriptor();
    virtual ~BlockDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(BlockDescriptor)

BlockDescriptor::BlockDescriptor() : omnetpp::cClassDescriptor("Block", "BaseOverlayMessage")
{
    propertynames = nullptr;
}

BlockDescriptor::~BlockDescriptor()
{
    delete[] propertynames;
}

bool BlockDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Block *>(obj)!=nullptr;
}

const char **BlockDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *BlockDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int BlockDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount() : 1;
}

unsigned int BlockDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *BlockDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "index",
    };
    return (field>=0 && field<1) ? fieldNames[field] : nullptr;
}

int BlockDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='i' && strcmp(fieldName, "index")==0) return base+0;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *BlockDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : nullptr;
}

const char **BlockDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *BlockDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int BlockDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    Block *pp = (Block *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *BlockDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Block *pp = (Block *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string BlockDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Block *pp = (Block *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getIndex());
        default: return "";
    }
}

bool BlockDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    Block *pp = (Block *)object; (void)pp;
    switch (field) {
        case 0: pp->setIndex(string2long(value)); return true;
        default: return false;
    }
}

const char *BlockDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *BlockDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    Block *pp = (Block *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(ExchangeAfterDownload)

ExchangeAfterDownload::ExchangeAfterDownload(const char *name, short kind) : ::omnetpp::cMessage(name,kind)
{
}

ExchangeAfterDownload::ExchangeAfterDownload(const ExchangeAfterDownload& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

ExchangeAfterDownload::~ExchangeAfterDownload()
{
}

ExchangeAfterDownload& ExchangeAfterDownload::operator=(const ExchangeAfterDownload& other)
{
    if (this==&other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void ExchangeAfterDownload::copy(const ExchangeAfterDownload& other)
{
    this->finished = other.finished;
}

void ExchangeAfterDownload::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->finished);
}

void ExchangeAfterDownload::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->finished);
}

TransportAddress& ExchangeAfterDownload::getFinished()
{
    return this->finished;
}

void ExchangeAfterDownload::setFinished(const TransportAddress& finished)
{
    this->finished = finished;
}

class ExchangeAfterDownloadDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    ExchangeAfterDownloadDescriptor();
    virtual ~ExchangeAfterDownloadDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(ExchangeAfterDownloadDescriptor)

ExchangeAfterDownloadDescriptor::ExchangeAfterDownloadDescriptor() : omnetpp::cClassDescriptor("ExchangeAfterDownload", "omnetpp::cMessage")
{
    propertynames = nullptr;
}

ExchangeAfterDownloadDescriptor::~ExchangeAfterDownloadDescriptor()
{
    delete[] propertynames;
}

bool ExchangeAfterDownloadDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<ExchangeAfterDownload *>(obj)!=nullptr;
}

const char **ExchangeAfterDownloadDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *ExchangeAfterDownloadDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int ExchangeAfterDownloadDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount() : 1;
}

unsigned int ExchangeAfterDownloadDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *ExchangeAfterDownloadDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "finished",
    };
    return (field>=0 && field<1) ? fieldNames[field] : nullptr;
}

int ExchangeAfterDownloadDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='f' && strcmp(fieldName, "finished")==0) return base+0;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *ExchangeAfterDownloadDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "TransportAddress",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : nullptr;
}

const char **ExchangeAfterDownloadDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *ExchangeAfterDownloadDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int ExchangeAfterDownloadDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    ExchangeAfterDownload *pp = (ExchangeAfterDownload *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *ExchangeAfterDownloadDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    ExchangeAfterDownload *pp = (ExchangeAfterDownload *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string ExchangeAfterDownloadDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    ExchangeAfterDownload *pp = (ExchangeAfterDownload *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getFinished(); return out.str();}
        default: return "";
    }
}

bool ExchangeAfterDownloadDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    ExchangeAfterDownload *pp = (ExchangeAfterDownload *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *ExchangeAfterDownloadDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0: return omnetpp::opp_typename(typeid(TransportAddress));
        default: return nullptr;
    };
}

void *ExchangeAfterDownloadDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    ExchangeAfterDownload *pp = (ExchangeAfterDownload *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getFinished()); break;
        default: return nullptr;
    }
}


