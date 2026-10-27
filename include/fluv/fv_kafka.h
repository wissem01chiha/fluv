#include <stdio.h>
#include <string.h>
#include <librdkafka/rdkafka.h>

static void on_delivery(rd_kafka_t* rk, const rd_kafka_message_t* msg, void* opaque) {
  if (msg->err)
    fprintf(stderr, "delivery failed: %s\n", rd_kafka_err2str(msg->err));
}

int main(void) {
  char errstr[512];
  rd_kafka_conf_t* conf = rd_kafka_conf_new();

  rd_kafka_conf_set(conf, "bootstrap.servers", "localhost:9092", errstr, sizeof errstr);
  rd_kafka_conf_set(conf, "enable.idempotence", "true", errstr, sizeof errstr);
  rd_kafka_conf_set(conf, "linger.ms", "5", errstr, sizeof errstr);
  rd_kafka_conf_set_dr_msg_cb(conf, on_delivery);

  rd_kafka_t* rk = rd_kafka_new(RD_KAFKA_PRODUCER, conf, errstr, sizeof errstr);
  if (!rk) { fprintf(stderr, "%s\n", errstr); return 1; }

  const char* key = "node-42";
  const char* payload = "{\"event\":\"node_failed\",\"node\":42}";

  rd_kafka_resp_err_t err = rd_kafka_producev(rk,
      RD_KAFKA_V_TOPIC("fluv.events"),
      RD_KAFKA_V_KEY(key, strlen(key)),
      RD_KAFKA_V_VALUE((void*)payload, strlen(payload)),
      RD_KAFKA_V_MSGFLAGS(RD_KAFKA_MSG_F_COPY),
      RD_KAFKA_V_END);

  if (err == RD_KAFKA_RESP_ERR__QUEUE_FULL)
    fprintf(stderr, "local queue full (back-pressure)\n");

  rd_kafka_poll(rk, 0);           /* serve delivery callbacks */
  rd_kafka_flush(rk, 10 * 1000);  /* wait for outstanding messages on shutdown */
  rd_kafka_destroy(rk);
  return 0;
}