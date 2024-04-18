//
// Generated file, do not edit! Created by nedtool 5.4 from overlay/coolstreaming/../coolstreaming/Coolstreaming.msg.
//

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#ifndef __COOLSTREAMING_M_H
#define __COOLSTREAMING_M_H

#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0504
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



// cplusplus {{
#include <chrono>
#include <vector>
#include <unordered_set>
#include "common/NodeHandle.h"
#include "common/OverlayKey.h"
#include "common/CommonMessages_m.h"
#include "common/TransportAddress.h"
typedef std::chrono::duration<int,std::milli> duration_ms;
typedef std::vector<TransportAddress> TadVec;
typedef std::unordered_set<int> BM;
// }}

/**
 * Class generated from <tt>overlay/coolstreaming/../coolstreaming/Coolstreaming.msg:45</tt> by nedtool.
 * <pre>
 * // scamp/mcache membership message
 * packet Membership extends BaseOverlayMessage
 * {
 *     int uuid; // to identify infinitely looping messages
 *     int seq_num;
 *     TransportAddress tad;
 *     int num_partner;
 *     simtime_t ttl;
 *     bool forwarded; // if this was forwarded or is the entry message for the node
 *     bool entry; // if this is the entry message for the node
 * }
 * </pre>
 */
class Membership : public ::BaseOverlayMessage
{
  protected:
    int uuid;
    int seq_num;
    TransportAddress tad;
    int num_partner;
    ::omnetpp::simtime_t ttl;
    bool forwarded;
    bool entry;

  private:
    void copy(const Membership& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Membership&);

  public:
    Membership(const char *name=nullptr, short kind=0);
    Membership(const Membership& other);
    virtual ~Membership();
    Membership& operator=(const Membership& other);
    virtual Membership *dup() const override {return new Membership(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual int getUuid() const;
    virtual void setUuid(int uuid);
    virtual int getSeq_num() const;
    virtual void setSeq_num(int seq_num);
    virtual TransportAddress& getTad();
    virtual const TransportAddress& getTad() const {return const_cast<Membership*>(this)->getTad();}
    virtual void setTad(const TransportAddress& tad);
    virtual int getNum_partner() const;
    virtual void setNum_partner(int num_partner);
    virtual ::omnetpp::simtime_t getTtl() const;
    virtual void setTtl(::omnetpp::simtime_t ttl);
    virtual bool getForwarded() const;
    virtual void setForwarded(bool forwarded);
    virtual bool getEntry() const;
    virtual void setEntry(bool entry);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Membership& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Membership& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>overlay/coolstreaming/../coolstreaming/Coolstreaming.msg:56</tt> by nedtool.
 * <pre>
 * // scamp/inview membership message
 * packet InviewCall extends BaseCallMessage
 * {
 *     TransportAddress destination;
 *     TransportAddress accepting_node;
 * }
 * </pre>
 */
class InviewCall : public ::BaseCallMessage
{
  protected:
    TransportAddress destination;
    TransportAddress accepting_node;

  private:
    void copy(const InviewCall& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const InviewCall&);

  public:
    InviewCall(const char *name=nullptr, short kind=0);
    InviewCall(const InviewCall& other);
    virtual ~InviewCall();
    InviewCall& operator=(const InviewCall& other);
    virtual InviewCall *dup() const override {return new InviewCall(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual TransportAddress& getDestination();
    virtual const TransportAddress& getDestination() const {return const_cast<InviewCall*>(this)->getDestination();}
    virtual void setDestination(const TransportAddress& destination);
    virtual TransportAddress& getAccepting_node();
    virtual const TransportAddress& getAccepting_node() const {return const_cast<InviewCall*>(this)->getAccepting_node();}
    virtual void setAccepting_node(const TransportAddress& accepting_node);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const InviewCall& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, InviewCall& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>overlay/coolstreaming/../coolstreaming/Coolstreaming.msg:62</tt> by nedtool.
 * <pre>
 * // scamp/inview insertion acknowledgement
 * packet InviewResponse extends BaseResponseMessage
 * {
 * }
 * </pre>
 */
class InviewResponse : public ::BaseResponseMessage
{
  protected:

  private:
    void copy(const InviewResponse& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const InviewResponse&);

  public:
    InviewResponse(const char *name=nullptr, short kind=0);
    InviewResponse(const InviewResponse& other);
    virtual ~InviewResponse();
    InviewResponse& operator=(const InviewResponse& other);
    virtual InviewResponse *dup() const override {return new InviewResponse(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const InviewResponse& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, InviewResponse& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>overlay/coolstreaming/../coolstreaming/Coolstreaming.msg:65</tt> by nedtool.
 * <pre>
 * // scamp/mcache unsubscription message
 * packet Unsubscription extends BaseOverlayMessage
 * {
 *     TransportAddress leaving;
 *     TransportAddress replacement;
 *     bool inview;
 * }
 * </pre>
 */
class Unsubscription : public ::BaseOverlayMessage
{
  protected:
    TransportAddress leaving;
    TransportAddress replacement;
    bool inview;

  private:
    void copy(const Unsubscription& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Unsubscription&);

  public:
    Unsubscription(const char *name=nullptr, short kind=0);
    Unsubscription(const Unsubscription& other);
    virtual ~Unsubscription();
    Unsubscription& operator=(const Unsubscription& other);
    virtual Unsubscription *dup() const override {return new Unsubscription(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual TransportAddress& getLeaving();
    virtual const TransportAddress& getLeaving() const {return const_cast<Unsubscription*>(this)->getLeaving();}
    virtual void setLeaving(const TransportAddress& leaving);
    virtual TransportAddress& getReplacement();
    virtual const TransportAddress& getReplacement() const {return const_cast<Unsubscription*>(this)->getReplacement();}
    virtual void setReplacement(const TransportAddress& replacement);
    virtual bool getInview() const;
    virtual void setInview(bool inview);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Unsubscription& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Unsubscription& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>overlay/coolstreaming/../coolstreaming/Coolstreaming.msg:73</tt> by nedtool.
 * <pre>
 * // coolstreaming-extended scamp gossiped unsubscription message .
 * // i feel the need to again mentino that this is a Very Fucking Bad Idea
 * packet GossipedUnsubscription extends BaseOverlayMessage
 * {
 *     TransportAddress from;
 *     TransportAddress failing;
 * }
 * </pre>
 */
class GossipedUnsubscription : public ::BaseOverlayMessage
{
  protected:
    TransportAddress from;
    TransportAddress failing;

  private:
    void copy(const GossipedUnsubscription& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const GossipedUnsubscription&);

  public:
    GossipedUnsubscription(const char *name=nullptr, short kind=0);
    GossipedUnsubscription(const GossipedUnsubscription& other);
    virtual ~GossipedUnsubscription();
    GossipedUnsubscription& operator=(const GossipedUnsubscription& other);
    virtual GossipedUnsubscription *dup() const override {return new GossipedUnsubscription(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual TransportAddress& getFrom();
    virtual const TransportAddress& getFrom() const {return const_cast<GossipedUnsubscription*>(this)->getFrom();}
    virtual void setFrom(const TransportAddress& from);
    virtual TransportAddress& getFailing();
    virtual const TransportAddress& getFailing() const {return const_cast<GossipedUnsubscription*>(this)->getFailing();}
    virtual void setFailing(const TransportAddress& failing);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const GossipedUnsubscription& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, GossipedUnsubscription& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>overlay/coolstreaming/../coolstreaming/Coolstreaming.msg:79</tt> by nedtool.
 * <pre>
 * // scamp/mcache heartbeat message
 * packet Heartbeat extends BaseOverlayMessage
 * {
 * }
 * </pre>
 */
class Heartbeat : public ::BaseOverlayMessage
{
  protected:

  private:
    void copy(const Heartbeat& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Heartbeat&);

  public:
    Heartbeat(const char *name=nullptr, short kind=0);
    Heartbeat(const Heartbeat& other);
    virtual ~Heartbeat();
    Heartbeat& operator=(const Heartbeat& other);
    virtual Heartbeat *dup() const override {return new Heartbeat(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Heartbeat& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Heartbeat& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>overlay/coolstreaming/../coolstreaming/Coolstreaming.msg:82</tt> by nedtool.
 * <pre>
 * // coolstreaming origin deputy list request message. also contains the starting block index
 * packet GetDeputyCall extends BaseCallMessage
 * {
 *     TransportAddress dest;
 * }
 * </pre>
 */
class GetDeputyCall : public ::BaseCallMessage
{
  protected:
    TransportAddress dest;

  private:
    void copy(const GetDeputyCall& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const GetDeputyCall&);

  public:
    GetDeputyCall(const char *name=nullptr, short kind=0);
    GetDeputyCall(const GetDeputyCall& other);
    virtual ~GetDeputyCall();
    GetDeputyCall& operator=(const GetDeputyCall& other);
    virtual GetDeputyCall *dup() const override {return new GetDeputyCall(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual TransportAddress& getDest();
    virtual const TransportAddress& getDest() const {return const_cast<GetDeputyCall*>(this)->getDest();}
    virtual void setDest(const TransportAddress& dest);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const GetDeputyCall& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, GetDeputyCall& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>overlay/coolstreaming/../coolstreaming/Coolstreaming.msg:86</tt> by nedtool.
 * <pre>
 * packet GetDeputyResponse extends BaseResponseMessage
 * {
 *     TransportAddress deputy;
 *     int block_index;
 * }
 * </pre>
 */
class GetDeputyResponse : public ::BaseResponseMessage
{
  protected:
    TransportAddress deputy;
    int block_index;

  private:
    void copy(const GetDeputyResponse& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const GetDeputyResponse&);

  public:
    GetDeputyResponse(const char *name=nullptr, short kind=0);
    GetDeputyResponse(const GetDeputyResponse& other);
    virtual ~GetDeputyResponse();
    GetDeputyResponse& operator=(const GetDeputyResponse& other);
    virtual GetDeputyResponse *dup() const override {return new GetDeputyResponse(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual TransportAddress& getDeputy();
    virtual const TransportAddress& getDeputy() const {return const_cast<GetDeputyResponse*>(this)->getDeputy();}
    virtual void setDeputy(const TransportAddress& deputy);
    virtual int getBlock_index() const;
    virtual void setBlock_index(int block_index);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const GetDeputyResponse& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, GetDeputyResponse& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>overlay/coolstreaming/../coolstreaming/Coolstreaming.msg:92</tt> by nedtool.
 * <pre>
 * // coolstreaming deputy partner list request message
 * packet GetCandidatePartnersCall extends BaseCallMessage
 * {
 *     TransportAddress from;
 * }
 * </pre>
 */
class GetCandidatePartnersCall : public ::BaseCallMessage
{
  protected:
    TransportAddress from;

  private:
    void copy(const GetCandidatePartnersCall& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const GetCandidatePartnersCall&);

  public:
    GetCandidatePartnersCall(const char *name=nullptr, short kind=0);
    GetCandidatePartnersCall(const GetCandidatePartnersCall& other);
    virtual ~GetCandidatePartnersCall();
    GetCandidatePartnersCall& operator=(const GetCandidatePartnersCall& other);
    virtual GetCandidatePartnersCall *dup() const override {return new GetCandidatePartnersCall(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual TransportAddress& getFrom();
    virtual const TransportAddress& getFrom() const {return const_cast<GetCandidatePartnersCall*>(this)->getFrom();}
    virtual void setFrom(const TransportAddress& from);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const GetCandidatePartnersCall& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, GetCandidatePartnersCall& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>overlay/coolstreaming/../coolstreaming/Coolstreaming.msg:96</tt> by nedtool.
 * <pre>
 * packet GetCandidatePartnersResponse extends BaseResponseMessage
 * {
 *     TadVec candidates;
 * }
 * </pre>
 */
class GetCandidatePartnersResponse : public ::BaseResponseMessage
{
  protected:
    TadVec candidates;

  private:
    void copy(const GetCandidatePartnersResponse& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const GetCandidatePartnersResponse&);

  public:
    GetCandidatePartnersResponse(const char *name=nullptr, short kind=0);
    GetCandidatePartnersResponse(const GetCandidatePartnersResponse& other);
    virtual ~GetCandidatePartnersResponse();
    GetCandidatePartnersResponse& operator=(const GetCandidatePartnersResponse& other);
    virtual GetCandidatePartnersResponse *dup() const override {return new GetCandidatePartnersResponse(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual TadVec& getCandidates();
    virtual const TadVec& getCandidates() const {return const_cast<GetCandidatePartnersResponse*>(this)->getCandidates();}
    virtual void setCandidates(const TadVec& candidates);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const GetCandidatePartnersResponse& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, GetCandidatePartnersResponse& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>overlay/coolstreaming/../coolstreaming/Coolstreaming.msg:101</tt> by nedtool.
 * <pre>
 * // coolstreaming partnership initiation/ending
 * packet Partnership extends BaseOverlayMessage
 * {
 *     TransportAddress from;
 * }
 * </pre>
 */
class Partnership : public ::BaseOverlayMessage
{
  protected:
    TransportAddress from;

  private:
    void copy(const Partnership& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Partnership&);

  public:
    Partnership(const char *name=nullptr, short kind=0);
    Partnership(const Partnership& other);
    virtual ~Partnership();
    Partnership& operator=(const Partnership& other);
    virtual Partnership *dup() const override {return new Partnership(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual TransportAddress& getFrom();
    virtual const TransportAddress& getFrom() const {return const_cast<Partnership*>(this)->getFrom();}
    virtual void setFrom(const TransportAddress& from);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Partnership& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Partnership& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>overlay/coolstreaming/../coolstreaming/Coolstreaming.msg:105</tt> by nedtool.
 * <pre>
 * packet PartnershipEnd extends BaseOverlayMessage
 * {
 *     TransportAddress from;
 * }
 * </pre>
 */
class PartnershipEnd : public ::BaseOverlayMessage
{
  protected:
    TransportAddress from;

  private:
    void copy(const PartnershipEnd& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const PartnershipEnd&);

  public:
    PartnershipEnd(const char *name=nullptr, short kind=0);
    PartnershipEnd(const PartnershipEnd& other);
    virtual ~PartnershipEnd();
    PartnershipEnd& operator=(const PartnershipEnd& other);
    virtual PartnershipEnd *dup() const override {return new PartnershipEnd(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual TransportAddress& getFrom();
    virtual const TransportAddress& getFrom() const {return const_cast<PartnershipEnd*>(this)->getFrom();}
    virtual void setFrom(const TransportAddress& from);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const PartnershipEnd& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, PartnershipEnd& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>overlay/coolstreaming/../coolstreaming/Coolstreaming.msg:110</tt> by nedtool.
 * <pre>
 * // coolstreaming buffermap exchange
 * packet BufferMap extends BaseOverlayMessage
 * {
 *     BM buffer_map;
 * }
 * </pre>
 */
class BufferMap : public ::BaseOverlayMessage
{
  protected:
    BM buffer_map;

  private:
    void copy(const BufferMap& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const BufferMap&);

  public:
    BufferMap(const char *name=nullptr, short kind=0);
    BufferMap(const BufferMap& other);
    virtual ~BufferMap();
    BufferMap& operator=(const BufferMap& other);
    virtual BufferMap *dup() const override {return new BufferMap(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual BM& getBuffer_map();
    virtual const BM& getBuffer_map() const {return const_cast<BufferMap*>(this)->getBuffer_map();}
    virtual void setBuffer_map(const BM& buffer_map);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const BufferMap& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, BufferMap& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>overlay/coolstreaming/../coolstreaming/Coolstreaming.msg:115</tt> by nedtool.
 * <pre>
 * // coolstreaming block request
 * packet BlockCall extends BaseCallMessage
 * {
 *     BM blocks;
 * }
 * </pre>
 */
class BlockCall : public ::BaseCallMessage
{
  protected:
    BM blocks;

  private:
    void copy(const BlockCall& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const BlockCall&);

  public:
    BlockCall(const char *name=nullptr, short kind=0);
    BlockCall(const BlockCall& other);
    virtual ~BlockCall();
    BlockCall& operator=(const BlockCall& other);
    virtual BlockCall *dup() const override {return new BlockCall(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual BM& getBlocks();
    virtual const BM& getBlocks() const {return const_cast<BlockCall*>(this)->getBlocks();}
    virtual void setBlocks(const BM& blocks);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const BlockCall& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, BlockCall& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>overlay/coolstreaming/../coolstreaming/Coolstreaming.msg:119</tt> by nedtool.
 * <pre>
 * packet BlockResponse extends BaseResponseMessage
 * {
 *     int index;
 * }
 * </pre>
 */
class BlockResponse : public ::BaseResponseMessage
{
  protected:
    int index;

  private:
    void copy(const BlockResponse& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const BlockResponse&);

  public:
    BlockResponse(const char *name=nullptr, short kind=0);
    BlockResponse(const BlockResponse& other);
    virtual ~BlockResponse();
    BlockResponse& operator=(const BlockResponse& other);
    virtual BlockResponse *dup() const override {return new BlockResponse(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual int getIndex() const;
    virtual void setIndex(int index);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const BlockResponse& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, BlockResponse& obj) {obj.parsimUnpack(b);}


#endif // ifndef __COOLSTREAMING_M_H

