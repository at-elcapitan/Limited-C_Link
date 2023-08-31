#include "commands.h"

void on_message_delete(struct discord *client,
                       const struct discord_message *event) {
  log_info("Clear called");

  struct discord_get_channel_messages params = {.limit = 10};
  struct discord_messages messages = {0};
  struct discord_ret_messages retMessages = {.sync = &messages};

  discord_get_channel_messages(client, event->channel_id, &params,
                               &retMessages);

  if (!messages.size) {
    return;
  }

  u64snowflake msgsArray[100];

  struct snowflakes msgsSflakes = {.array = msgsArray, .size = messages.size};

  for (short x = 0; x != messages.size; ++x) {
    msgsSflakes.array[x] = messages.array[x].id;
  }

  struct discord_ret retDelete = {.sync = true};
  struct discord_bulk_delete_messages deleteParams = {
      .messages = &msgsSflakes, .reason = "Administrator delete"};

  discord_bulk_delete_messages(client, event->channel_id, &deleteParams,
                               &retDelete);
};
