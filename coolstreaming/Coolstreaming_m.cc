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
}

void GetDeputyResponse::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::BaseResponseMessage::parsimPack(b);
    doParsimPacking(b,this->deputy);
}

void GetDeputyResponse::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::BaseResponseMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->deputy);
}

TransportAddress& GetDeputyResponse::getDeputy()
{
    return this->deputy;
}

void GetDeputyResponse::setDeputy(const TransportAddress& deputy)
{
    this->deputy = deputy;
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
    return basedesc ? 1+basedesc->getFieldCount() : 1;
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
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
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
    };
    return (field>=0 && field<1) ? fieldNames[field] : nullptr;
}

int GetDeputyResponseDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='d' && strcmp(fieldName, "deputy")==0) return base+0;
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
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : nullptr;
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

Register_Class(Partnership)

Partnership::Partnership(const char *name, short kind) : ::BaseOverlayMessage(name,kind)
{
    this->bandwidth = 0;
}

Partnership::Partnership(const Partnership& other) : ::BaseOverlayMessage(other)
{
    copy(other);
}

Partnership::~Partnership()
{
}

Partnership& Partnership::operator=(const Partnership& other)
{
    if (this==&other) return *this;
    ::BaseOverlayMessage::operator=(other);
    copy(other);
    return *this;
}

void Partnership::copy(const Partnership& other)
{
    this->from = other.from;
    this->bandwidth = other.bandwidth;
}

void Partnership::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::BaseOverlayMessage::parsimPack(b);
    doParsimPacking(b,this->from);
    doParsimPacking(b,this->bandwidth);
}

void Partnership::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::BaseOverlayMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->from);
    doParsimUnpacking(b,this->bandwidth);
}

TransportAddress& Partnership::getFrom()
{
    return this->from;
}

void Partnership::setFrom(const TransportAddress& from)
{
    this->from = from;
}

double Partnership::getBandwidth() const
{
    return this->bandwidth;
}

void Partnership::setBandwidth(double bandwidth)
{
    this->bandwidth = bandwidth;
}

class PartnershipDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    PartnershipDescriptor();
    virtual ~PartnershipDescriptor();

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

Register_ClassDescriptor(PartnershipDescriptor)

PartnershipDescriptor::PartnershipDescriptor() : omnetpp::cClassDescriptor("Partnership", "BaseOverlayMessage")
{
    propertynames = nullptr;
}

PartnershipDescriptor::~PartnershipDescriptor()
{
    delete[] propertynames;
}

bool PartnershipDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Partnership *>(obj)!=nullptr;
}

const char **PartnershipDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *PartnershipDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int PartnershipDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount() : 2;
}

unsigned int PartnershipDescriptor::getFieldTypeFlags(int field) const
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

const char *PartnershipDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "from",
        "bandwidth",
    };
    return (field>=0 && field<2) ? fieldNames[field] : nullptr;
}

int PartnershipDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='f' && strcmp(fieldName, "from")==0) return base+0;
    if (fieldName[0]=='b' && strcmp(fieldName, "bandwidth")==0) return base+1;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *PartnershipDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "TransportAddress",
        "double",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : nullptr;
}

const char **PartnershipDescriptor::getFieldPropertyNames(int field) const
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

const char *PartnershipDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int PartnershipDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    Partnership *pp = (Partnership *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *PartnershipDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Partnership *pp = (Partnership *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string PartnershipDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Partnership *pp = (Partnership *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getFrom(); return out.str();}
        case 1: return double2string(pp->getBandwidth());
        default: return "";
    }
}

bool PartnershipDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    Partnership *pp = (Partnership *)object; (void)pp;
    switch (field) {
        case 1: pp->setBandwidth(string2double(value)); return true;
        default: return false;
    }
}

const char *PartnershipDescriptor::getFieldStructName(int field) const
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

void *PartnershipDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    Partnership *pp = (Partnership *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getFrom()); break;
        default: return nullptr;
    }
}

Register_Class(PartnershipEnd)

PartnershipEnd::PartnershipEnd(const char *name, short kind) : ::BaseOverlayMessage(name,kind)
{
}

PartnershipEnd::PartnershipEnd(const PartnershipEnd& other) : ::BaseOverlayMessage(other)
{
    copy(other);
}

PartnershipEnd::~PartnershipEnd()
{
}

PartnershipEnd& PartnershipEnd::operator=(const PartnershipEnd& other)
{
    if (this==&other) return *this;
    ::BaseOverlayMessage::operator=(other);
    copy(other);
    return *this;
}

void PartnershipEnd::copy(const PartnershipEnd& other)
{
    this->from = other.from;
}

void PartnershipEnd::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::BaseOverlayMessage::parsimPack(b);
    doParsimPacking(b,this->from);
}

void PartnershipEnd::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::BaseOverlayMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->from);
}

TransportAddress& PartnershipEnd::getFrom()
{
    return this->from;
}

void PartnershipEnd::setFrom(const TransportAddress& from)
{
    this->from = from;
}

class PartnershipEndDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    PartnershipEndDescriptor();
    virtual ~PartnershipEndDescriptor();

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

Register_ClassDescriptor(PartnershipEndDescriptor)

PartnershipEndDescriptor::PartnershipEndDescriptor() : omnetpp::cClassDescriptor("PartnershipEnd", "BaseOverlayMessage")
{
    propertynames = nullptr;
}

PartnershipEndDescriptor::~PartnershipEndDescriptor()
{
    delete[] propertynames;
}

bool PartnershipEndDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<PartnershipEnd *>(obj)!=nullptr;
}

const char **PartnershipEndDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *PartnershipEndDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int PartnershipEndDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount() : 1;
}

unsigned int PartnershipEndDescriptor::getFieldTypeFlags(int field) const
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

const char *PartnershipEndDescriptor::getFieldName(int field) const
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

int PartnershipEndDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='f' && strcmp(fieldName, "from")==0) return base+0;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *PartnershipEndDescriptor::getFieldTypeString(int field) const
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

const char **PartnershipEndDescriptor::getFieldPropertyNames(int field) const
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

const char *PartnershipEndDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int PartnershipEndDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    PartnershipEnd *pp = (PartnershipEnd *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *PartnershipEndDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    PartnershipEnd *pp = (PartnershipEnd *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string PartnershipEndDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    PartnershipEnd *pp = (PartnershipEnd *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getFrom(); return out.str();}
        default: return "";
    }
}

bool PartnershipEndDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    PartnershipEnd *pp = (PartnershipEnd *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *PartnershipEndDescriptor::getFieldStructName(int field) const
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

void *PartnershipEndDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    PartnershipEnd *pp = (PartnershipEnd *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getFrom()); break;
        default: return nullptr;
    }
}

Register_Class(BufferMapMsg)

BufferMapMsg::BufferMapMsg(const char *name, short kind) : ::BaseOverlayMessage(name,kind)
{
}

BufferMapMsg::BufferMapMsg(const BufferMapMsg& other) : ::BaseOverlayMessage(other)
{
    copy(other);
}

BufferMapMsg::~BufferMapMsg()
{
}

BufferMapMsg& BufferMapMsg::operator=(const BufferMapMsg& other)
{
    if (this==&other) return *this;
    ::BaseOverlayMessage::operator=(other);
    copy(other);
    return *this;
}

void BufferMapMsg::copy(const BufferMapMsg& other)
{
    this->from = other.from;
    this->buffer_map = other.buffer_map;
}

void BufferMapMsg::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::BaseOverlayMessage::parsimPack(b);
    doParsimPacking(b,this->from);
    doParsimPacking(b,this->buffer_map);
}

void BufferMapMsg::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::BaseOverlayMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->from);
    doParsimUnpacking(b,this->buffer_map);
}

TransportAddress& BufferMapMsg::getFrom()
{
    return this->from;
}

void BufferMapMsg::setFrom(const TransportAddress& from)
{
    this->from = from;
}

BufferMap& BufferMapMsg::getBuffer_map()
{
    return this->buffer_map;
}

void BufferMapMsg::setBuffer_map(const BufferMap& buffer_map)
{
    this->buffer_map = buffer_map;
}

class BufferMapMsgDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    BufferMapMsgDescriptor();
    virtual ~BufferMapMsgDescriptor();

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

Register_ClassDescriptor(BufferMapMsgDescriptor)

BufferMapMsgDescriptor::BufferMapMsgDescriptor() : omnetpp::cClassDescriptor("BufferMapMsg", "BaseOverlayMessage")
{
    propertynames = nullptr;
}

BufferMapMsgDescriptor::~BufferMapMsgDescriptor()
{
    delete[] propertynames;
}

bool BufferMapMsgDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<BufferMapMsg *>(obj)!=nullptr;
}

const char **BufferMapMsgDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *BufferMapMsgDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int BufferMapMsgDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount() : 2;
}

unsigned int BufferMapMsgDescriptor::getFieldTypeFlags(int field) const
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

const char *BufferMapMsgDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "from",
        "buffer_map",
    };
    return (field>=0 && field<2) ? fieldNames[field] : nullptr;
}

int BufferMapMsgDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='f' && strcmp(fieldName, "from")==0) return base+0;
    if (fieldName[0]=='b' && strcmp(fieldName, "buffer_map")==0) return base+1;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *BufferMapMsgDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "TransportAddress",
        "BufferMap",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : nullptr;
}

const char **BufferMapMsgDescriptor::getFieldPropertyNames(int field) const
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

const char *BufferMapMsgDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int BufferMapMsgDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    BufferMapMsg *pp = (BufferMapMsg *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *BufferMapMsgDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    BufferMapMsg *pp = (BufferMapMsg *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string BufferMapMsgDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    BufferMapMsg *pp = (BufferMapMsg *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getFrom(); return out.str();}
        case 1: {std::stringstream out; out << pp->getBuffer_map(); return out.str();}
        default: return "";
    }
}

bool BufferMapMsgDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    BufferMapMsg *pp = (BufferMapMsg *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *BufferMapMsgDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0: return omnetpp::opp_typename(typeid(TransportAddress));
        case 1: return omnetpp::opp_typename(typeid(BufferMap));
        default: return nullptr;
    };
}

void *BufferMapMsgDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    BufferMapMsg *pp = (BufferMapMsg *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getFrom()); break;
        case 1: return (void *)(&pp->getBuffer_map()); break;
        default: return nullptr;
    }
}

Register_Class(Block)

Block::Block(const char *name, short kind) : ::BaseOverlayMessage(name,kind)
{
    this->index = 0;
    this->triggers_send = false;
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
    this->triggers_send = other.triggers_send;
}

void Block::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::BaseOverlayMessage::parsimPack(b);
    doParsimPacking(b,this->index);
    doParsimPacking(b,this->triggers_send);
}

void Block::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::BaseOverlayMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->index);
    doParsimUnpacking(b,this->triggers_send);
}

int Block::getIndex() const
{
    return this->index;
}

void Block::setIndex(int index)
{
    this->index = index;
}

bool Block::getTriggers_send() const
{
    return this->triggers_send;
}

void Block::setTriggers_send(bool triggers_send)
{
    this->triggers_send = triggers_send;
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
    return basedesc ? 2+basedesc->getFieldCount() : 2;
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
        FD_ISEDITABLE,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
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
        "triggers_send",
    };
    return (field>=0 && field<2) ? fieldNames[field] : nullptr;
}

int BlockDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='i' && strcmp(fieldName, "index")==0) return base+0;
    if (fieldName[0]=='t' && strcmp(fieldName, "triggers_send")==0) return base+1;
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
        "bool",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : nullptr;
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
        case 1: return bool2string(pp->getTriggers_send());
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
        case 1: pp->setTriggers_send(string2bool(value)); return true;
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


