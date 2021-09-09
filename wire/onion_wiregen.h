/* This file was generated by generate-wire.py */
/* Do not modify this file! Modify the _csv file it was generated from. */
/* Original template can be found at tools/gen/header_template */

#ifndef LIGHTNING_WIRE_ONION_WIREGEN_H
#define LIGHTNING_WIRE_ONION_WIREGEN_H
#include <ccan/tal/tal.h>
#include <wire/tlvstream.h>
#include <wire/wire.h>
#include <bitcoin/short_channel_id.h>
#include <bitcoin/privkey.h>
#include <common/bigsize.h>
#include <common/amount.h>
#include <common/node_id.h>
#include <bitcoin/block.h>
#include <wire/onion_defs.h>

enum onion_wire {
        WIRE_INVALID_REALM = PERM|1,
        WIRE_TEMPORARY_NODE_FAILURE = NODE|2,
        WIRE_PERMANENT_NODE_FAILURE = PERM|NODE|2,
        WIRE_REQUIRED_NODE_FEATURE_MISSING = PERM|NODE|3,
        WIRE_INVALID_ONION_VERSION = BADONION|PERM|4,
        WIRE_INVALID_ONION_HMAC = BADONION|PERM|5,
        WIRE_INVALID_ONION_KEY = BADONION|PERM|6,
        WIRE_TEMPORARY_CHANNEL_FAILURE = UPDATE|7,
        WIRE_PERMANENT_CHANNEL_FAILURE = PERM|8,
        WIRE_REQUIRED_CHANNEL_FEATURE_MISSING = PERM|9,
        WIRE_UNKNOWN_NEXT_PEER = PERM|10,
        WIRE_AMOUNT_BELOW_MINIMUM = UPDATE|11,
        WIRE_FEE_INSUFFICIENT = UPDATE|12,
        WIRE_INCORRECT_CLTV_EXPIRY = UPDATE|13,
        WIRE_EXPIRY_TOO_SOON = UPDATE|14,
        WIRE_INCORRECT_OR_UNKNOWN_PAYMENT_DETAILS = PERM|15,
        WIRE_FINAL_INCORRECT_CLTV_EXPIRY = 18,
        WIRE_FINAL_INCORRECT_HTLC_AMOUNT = 19,
        WIRE_CHANNEL_DISABLED = UPDATE|20,
        WIRE_EXPIRY_TOO_FAR = 21,
        WIRE_INVALID_ONION_PAYLOAD = PERM|22,
        WIRE_MPP_TIMEOUT = 23,
};

const char *onion_wire_name(int e);

/**
 * Determine whether a given message type is defined as a message.
 *
 * Returns true if the message type is part of the message definitions we have
 * generated parsers for, false if it is a custom message that cannot be
 * handled internally.
 */
bool onion_wire_is_defined(u16 type);

struct onionmsg_path {
        struct pubkey node_id;
        u8 *enctlv;
};
struct tlv_tlv_payload_payment_data {
        struct secret payment_secret;
        u64 total_msat;
};
struct tlv_onionmsg_payload_reply_path {
        struct pubkey blinding;
        struct onionmsg_path **path;
};
struct tlv_tlv_payload {
        /* Raw fields including unknown ones. */
        struct tlv_field *fields;

	/* TODO The following explicit fields could just point into the
	 * tlv_field entries above to save on memory. */
	u64 *amt_to_forward;
	u32 *outgoing_cltv_value;
	struct short_channel_id *short_channel_id;
        struct tlv_tlv_payload_payment_data *payment_data;
};
struct tlv_onionmsg_payload {
        /* Raw fields including unknown ones. */
        struct tlv_field *fields;

	/* TODO The following explicit fields could just point into the
	 * tlv_field entries above to save on memory. */
	struct pubkey *next_node_id;
	struct short_channel_id *next_short_channel_id;
        struct tlv_onionmsg_payload_reply_path *reply_path;
	u8 *enctlv;
	struct pubkey *blinding;
	u8 *invoice_request;
	u8 *invoice;
	u8 *invoice_error;
};
struct tlv_encmsg_tlvs {
        /* Raw fields including unknown ones. */
        struct tlv_field *fields;

	/* TODO The following explicit fields could just point into the
	 * tlv_field entries above to save on memory. */
	struct pubkey *next_node_id;
	struct short_channel_id *next_short_channel_id;
};

struct tlv_tlv_payload *tlv_tlv_payload_new(const tal_t *ctx);

/**
 * Deserialize a TLV stream for the tlv_payload namespace.
 *
 * This function will parse any TLV stream, as long as the type, length and
 * value fields are formatted correctly. Fields that are not known in the
 * current namespace are stored in the `fields` member. Validity can be
 * checked using tlv_payload_is_valid.
 */
bool fromwire_tlv_payload(const u8 **cursor, size_t *max,
			  struct tlv_tlv_payload * record);

/**
 * Serialize a TLV stream for the tlv_payload namespace.
 *
 * This function only considers known fields from the tlv_payload namespace,
 * and will ignore any fields that may be stored in the `fields` member. This
 * ensures that the resulting stream is valid according to
 * `tlv_payload_is_valid`.
 */
void towire_tlv_payload(u8 **pptr, const struct tlv_tlv_payload *record);

/**
 * Check that the TLV stream is valid.
 *
 * Enforces the followin validity rules:
 * - Types must be in monotonic non-repeating order
 * - We must understand all even types
 *
 * Returns false if an error was detected, otherwise returns true. If err_index
 * is non-null and we detect an error it is set to the index of the first error
 * detected.
 */
bool tlv_payload_is_valid(const struct tlv_tlv_payload *record,
			  size_t *err_index);

#define TLVS_ARRAY_SIZE_tlv_payload 4
extern const struct tlv_record_type tlvs_tlv_payload[];



/* Define an enum with the constants */
enum tlv_payload_types {
	TLV_TLV_PAYLOAD_AMT_TO_FORWARD = 2,
	TLV_TLV_PAYLOAD_OUTGOING_CLTV_VALUE = 4,
	TLV_TLV_PAYLOAD_SHORT_CHANNEL_ID = 6,
	TLV_TLV_PAYLOAD_PAYMENT_DATA = 8,
};

struct tlv_onionmsg_payload *tlv_onionmsg_payload_new(const tal_t *ctx);

/**
 * Deserialize a TLV stream for the onionmsg_payload namespace.
 *
 * This function will parse any TLV stream, as long as the type, length and
 * value fields are formatted correctly. Fields that are not known in the
 * current namespace are stored in the `fields` member. Validity can be
 * checked using onionmsg_payload_is_valid.
 */
bool fromwire_onionmsg_payload(const u8 **cursor, size_t *max,
			  struct tlv_onionmsg_payload * record);

/**
 * Serialize a TLV stream for the onionmsg_payload namespace.
 *
 * This function only considers known fields from the onionmsg_payload namespace,
 * and will ignore any fields that may be stored in the `fields` member. This
 * ensures that the resulting stream is valid according to
 * `onionmsg_payload_is_valid`.
 */
void towire_onionmsg_payload(u8 **pptr, const struct tlv_onionmsg_payload *record);

/**
 * Check that the TLV stream is valid.
 *
 * Enforces the followin validity rules:
 * - Types must be in monotonic non-repeating order
 * - We must understand all even types
 *
 * Returns false if an error was detected, otherwise returns true. If err_index
 * is non-null and we detect an error it is set to the index of the first error
 * detected.
 */
bool onionmsg_payload_is_valid(const struct tlv_onionmsg_payload *record,
			  size_t *err_index);

struct tlv_encmsg_tlvs *tlv_encmsg_tlvs_new(const tal_t *ctx);

/**
 * Deserialize a TLV stream for the encmsg_tlvs namespace.
 *
 * This function will parse any TLV stream, as long as the type, length and
 * value fields are formatted correctly. Fields that are not known in the
 * current namespace are stored in the `fields` member. Validity can be
 * checked using encmsg_tlvs_is_valid.
 */
bool fromwire_encmsg_tlvs(const u8 **cursor, size_t *max,
			  struct tlv_encmsg_tlvs * record);

/**
 * Serialize a TLV stream for the encmsg_tlvs namespace.
 *
 * This function only considers known fields from the encmsg_tlvs namespace,
 * and will ignore any fields that may be stored in the `fields` member. This
 * ensures that the resulting stream is valid according to
 * `encmsg_tlvs_is_valid`.
 */
void towire_encmsg_tlvs(u8 **pptr, const struct tlv_encmsg_tlvs *record);

/**
 * Check that the TLV stream is valid.
 *
 * Enforces the followin validity rules:
 * - Types must be in monotonic non-repeating order
 * - We must understand all even types
 *
 * Returns false if an error was detected, otherwise returns true. If err_index
 * is non-null and we detect an error it is set to the index of the first error
 * detected.
 */
bool encmsg_tlvs_is_valid(const struct tlv_encmsg_tlvs *record,
			  size_t *err_index);

/* SUBTYPE: ONIONMSG_PATH */
void towire_onionmsg_path(u8 **p, const struct onionmsg_path *onionmsg_path);
struct onionmsg_path *fromwire_onionmsg_path(const tal_t *ctx, const u8 **cursor, size_t *plen);

/* WIRE: INVALID_REALM */
u8 *towire_invalid_realm(const tal_t *ctx);
bool fromwire_invalid_realm(const void *p);

/* WIRE: TEMPORARY_NODE_FAILURE */
u8 *towire_temporary_node_failure(const tal_t *ctx);
bool fromwire_temporary_node_failure(const void *p);

/* WIRE: PERMANENT_NODE_FAILURE */
u8 *towire_permanent_node_failure(const tal_t *ctx);
bool fromwire_permanent_node_failure(const void *p);

/* WIRE: REQUIRED_NODE_FEATURE_MISSING */
u8 *towire_required_node_feature_missing(const tal_t *ctx);
bool fromwire_required_node_feature_missing(const void *p);

/* WIRE: INVALID_ONION_VERSION */
u8 *towire_invalid_onion_version(const tal_t *ctx, const struct sha256 *sha256_of_onion);
bool fromwire_invalid_onion_version(const void *p, struct sha256 *sha256_of_onion);

/* WIRE: INVALID_ONION_HMAC */
u8 *towire_invalid_onion_hmac(const tal_t *ctx, const struct sha256 *sha256_of_onion);
bool fromwire_invalid_onion_hmac(const void *p, struct sha256 *sha256_of_onion);

/* WIRE: INVALID_ONION_KEY */
u8 *towire_invalid_onion_key(const tal_t *ctx, const struct sha256 *sha256_of_onion);
bool fromwire_invalid_onion_key(const void *p, struct sha256 *sha256_of_onion);

/* WIRE: TEMPORARY_CHANNEL_FAILURE */
u8 *towire_temporary_channel_failure(const tal_t *ctx, const u8 *channel_update);
bool fromwire_temporary_channel_failure(const tal_t *ctx, const void *p, u8 **channel_update);

/* WIRE: PERMANENT_CHANNEL_FAILURE */
u8 *towire_permanent_channel_failure(const tal_t *ctx);
bool fromwire_permanent_channel_failure(const void *p);

/* WIRE: REQUIRED_CHANNEL_FEATURE_MISSING */
u8 *towire_required_channel_feature_missing(const tal_t *ctx);
bool fromwire_required_channel_feature_missing(const void *p);

/* WIRE: UNKNOWN_NEXT_PEER */
u8 *towire_unknown_next_peer(const tal_t *ctx);
bool fromwire_unknown_next_peer(const void *p);

/* WIRE: AMOUNT_BELOW_MINIMUM */
u8 *towire_amount_below_minimum(const tal_t *ctx, struct amount_msat htlc_msat, const u8 *channel_update);
bool fromwire_amount_below_minimum(const tal_t *ctx, const void *p, struct amount_msat *htlc_msat, u8 **channel_update);

/* WIRE: FEE_INSUFFICIENT */
u8 *towire_fee_insufficient(const tal_t *ctx, struct amount_msat htlc_msat, const u8 *channel_update);
bool fromwire_fee_insufficient(const tal_t *ctx, const void *p, struct amount_msat *htlc_msat, u8 **channel_update);

/* WIRE: INCORRECT_CLTV_EXPIRY */
u8 *towire_incorrect_cltv_expiry(const tal_t *ctx, u32 cltv_expiry, const u8 *channel_update);
bool fromwire_incorrect_cltv_expiry(const tal_t *ctx, const void *p, u32 *cltv_expiry, u8 **channel_update);

/* WIRE: EXPIRY_TOO_SOON */
u8 *towire_expiry_too_soon(const tal_t *ctx, const u8 *channel_update);
bool fromwire_expiry_too_soon(const tal_t *ctx, const void *p, u8 **channel_update);

/* WIRE: INCORRECT_OR_UNKNOWN_PAYMENT_DETAILS */
u8 *towire_incorrect_or_unknown_payment_details(const tal_t *ctx, struct amount_msat htlc_msat, u32 height);
bool fromwire_incorrect_or_unknown_payment_details(const void *p, struct amount_msat *htlc_msat, u32 *height);

/* WIRE: FINAL_INCORRECT_CLTV_EXPIRY */
u8 *towire_final_incorrect_cltv_expiry(const tal_t *ctx, u32 cltv_expiry);
bool fromwire_final_incorrect_cltv_expiry(const void *p, u32 *cltv_expiry);

/* WIRE: FINAL_INCORRECT_HTLC_AMOUNT */
u8 *towire_final_incorrect_htlc_amount(const tal_t *ctx, struct amount_msat incoming_htlc_amt);
bool fromwire_final_incorrect_htlc_amount(const void *p, struct amount_msat *incoming_htlc_amt);

/* WIRE: CHANNEL_DISABLED */
u8 *towire_channel_disabled(const tal_t *ctx);
bool fromwire_channel_disabled(const void *p);

/* WIRE: EXPIRY_TOO_FAR */
u8 *towire_expiry_too_far(const tal_t *ctx);
bool fromwire_expiry_too_far(const void *p);

/* WIRE: INVALID_ONION_PAYLOAD */
u8 *towire_invalid_onion_payload(const tal_t *ctx, bigsize type, u16 offset);
bool fromwire_invalid_onion_payload(const void *p, bigsize *type, u16 *offset);

/* WIRE: MPP_TIMEOUT */
u8 *towire_mpp_timeout(const tal_t *ctx);
bool fromwire_mpp_timeout(const void *p);


#endif /* LIGHTNING_WIRE_ONION_WIREGEN_H */
// SHA256STAMP:09dc1e023332a80d6e5b948472d121823404a3d7bfc843142b00ead7892148a1
