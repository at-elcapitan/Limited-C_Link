/**
 * at_c/link (c) by alice
 *
 * at_c/link is licensed under a
 * creative commons attribution-noncommercial-noderivatives 4.0 international
 * license.
 *
 * you should have received a copy of the license along with this
 * work. if not, see <http://creativecommons.org/licenses/by-nc-nd/4.0/>.
 */
 
#include "eventhandler.h"

GHashTable *connectedUsers;

void events_init() {
  connectedUsers = g_hash_table_new(g_str_hash, g_str_equal);
}

json_t *loadIChannels() {
  FILE *f = fopen("channels.json", "r+");

  if (f == NULL) {
    log_info("Error while opening file `channels.json`");
    return NULL;
  }

  char buffer[1024];
  int len = fread(buffer, 1, sizeof(buffer), f);
  fclose(f);

  json_error_t error;
  json_t *data = json_loads(buffer, 0, &error);
  json_t *retval = json_object_get(data, "ignorred_channels");

  free(data);
  return retval;
}

void on_voice_state_update(struct discord *client,
                           const struct discord_voice_state *event) {
  char desstring[19];

  struct ccord_szbuf_readonly value;
  struct discord_embed embed = {.timestamp = discord_timestamp(client)};
  value =
      discord_config_get_field(client, (char *[2]){"logging_channels", "1"}, 2);
  u64snowflake channelID = strtol(value.start, NULL, 10);

  char userID[19];
  char userchannelID[19];

  sprintf(desstring, "%ld", event->member->user->id);
  strcpy(userID, desstring);
  sprintf(desstring, "%ld", event->channel_id);
  strcpy(userchannelID, desstring);

  if (g_hash_table_contains(connectedUsers, userID) && !event->channel_id) {
    embed.color = 0xFF0000;
    discord_embed_set_description(
        &embed, "<@%ld> **disconnected from the voice channel** <#%s>",
        event->member->user->id, g_hash_table_lookup(connectedUsers, userID));

    g_hash_table_remove(connectedUsers, userID);
  } else if (g_hash_table_contains(connectedUsers, userID) &&
             event->channel_id) {
    return;
  } else {
    g_hash_table_insert(connectedUsers, userID, strdup(userchannelID));

    embed.color = 0x7070C7;
    discord_embed_set_description(
        &embed, "<@%ld> **connected to the voice channel** <#%ld>",
        event->member->user->id, event->channel_id);
  }

  if (strcmp(event->member->user->discriminator, "0")) {
    sprintf(desstring, "#%s", event->member->user->discriminator);
  } else {
    strcpy(desstring, "");
  }

  discord_embed_set_title(&embed, "%s%s", event->member->user->username,
                          desstring);

  struct discord_create_message params = {
      .embeds = &(struct discord_embeds){.size = 1, .array = &embed}};

  discord_create_message(client, channelID, &params, NULL);
  discord_embed_cleanup(&embed);
}

void on_message_update(struct discord *client,
                       const struct discord_message *event) {
  json_t *IChannels = loadIChannels();

  for (int x = 0; x != json_array_size(IChannels); ++x) {
    unsigned long long val =
        strtoull(json_string_value(json_array_get(IChannels, x)), NULL, 10);

    if (val == event->channel_id) {
      return;
    }
  }

  free(IChannels);

  struct ccord_szbuf_readonly value, val;
  struct discord_embed embed = {.timestamp = discord_timestamp(client),
                                .color = 0x0707C};
  value =
      discord_config_get_field(client, (char *[2]){"logging_channels", "1"}, 2);
  u64snowflake channelID = strtol(value.start, NULL, 10);

  char strg[50];
  if (strcmp(event->author->discriminator, "0")) {
    sprintf(strg, "#%s", event->author->discriminator);
  }

  discord_embed_set_title(&embed, "%s%s", event->author->username, strg);

  sprintf(strg, "User ID: %ld", event->author->id);

  discord_embed_set_footer(&embed, strg, NULL, NULL);
  discord_embed_set_description(
      &embed,
      "Message edited in <#%ld>\n[Goto "
      "message](https://discordapp.com/channels/%ld/%ld/%ld)",
      event->channel_id, event->guild_id, event->channel_id, event->id);

  discord_embed_add_field(&embed, "After", event->content, false);

  struct discord_create_message params = {
      .embeds = &(struct discord_embeds){.size = 1, .array = &embed}};

  discord_create_message(client, channelID, &params, NULL);
  discord_embed_cleanup(&embed);
};

void on_message_delete(struct discord *client,
                       const struct discord_message_delete *event) {
  json_t *IChannels = loadIChannels();

  for (int x = 0; x != json_array_size(IChannels); ++x) {
    unsigned long long val =
        strtoull(json_string_value(json_array_get(IChannels, x)), NULL, 10);

    if (val == event->channel_id) {
      return;
    }
  }

  free(IChannels);

  struct ccord_szbuf_readonly value;
  struct discord_embed embed = {.timestamp = discord_timestamp(client),
                                .color = 0x0707C};
  value =
      discord_config_get_field(client, (char *[2]){"logging_channels", "1"}, 2);
  u64snowflake channelID = strtol(value.start, NULL, 10);

  discord_embed_set_title(&embed, "Message deleted");
  discord_embed_set_description(&embed, "**Channel:** <#%ld>\nMessage ID: %ld",
                                event->channel_id, event->id);

  struct discord_create_message params = {
      .embeds = &(struct discord_embeds){.size = 1, .array = &embed}};

  discord_create_message(client, channelID, &params, NULL);
  discord_embed_cleanup(&embed);
}

void on_channel_create(struct discord *client,
                       const struct discord_channel *event) {
  struct ccord_szbuf_readonly value;
  struct discord_embed embed = {.timestamp = discord_timestamp(client),
                                .color = 0x7070C7};
  value =
      discord_config_get_field(client, (char *[2]){"logging_channels", "1"}, 2);
  u64snowflake channelID = strtol(value.start, NULL, 10);

  discord_embed_set_title(&embed, "Channel created");

  char channelType[30];

  switch (event->type) {
  case 0:
    strcpy(channelType, "Text channel (0)");
    break;
  case 2:
    strcpy(channelType, "Voice channel (2)");
    break;
  case 15:
    strcpy(channelType, "Forum (15)");
    break;
  case 5:
    strcpy(channelType, "Announcement Channel (5)");
    break;
  case 13:
    strcpy(channelType, "Stage (13)");
    break;
  default:
    strcpy(channelType, "Undefined (UNDEF)");
    break;
  }

  char strg[20];
  sprintf(strg, "ID: %ld", event->id);

  discord_embed_set_footer(&embed, strg, NULL, NULL);
  discord_embed_set_description(&embed, "Channel: <#%ld>\nChannel Type: `%s`",
                                event->id, channelType);

  struct discord_create_message params = {
      .embeds = &(struct discord_embeds){.size = 1, .array = &embed}};

  discord_create_message(client, channelID, &params, NULL);
  discord_embed_cleanup(&embed);
}

void on_channel_delete(struct discord *client,
                       const struct discord_channel *event) {
  struct ccord_szbuf_readonly value;
  struct discord_embed embed = {.timestamp = discord_timestamp(client),
                                .color = 0xFF0000};
  value =
      discord_config_get_field(client, (char *[2]){"logging_channels", "1"}, 2);
  u64snowflake channelID = strtol(value.start, NULL, 10);

  char strg[20];
  sprintf(strg, "ID: %ld", event->id);

  discord_embed_set_footer(&embed, strg, NULL, NULL);
  discord_embed_set_title(&embed, "Channel deleted");
  discord_embed_set_description(&embed, "Channel Name: `%s`\nPosition: `%d`",
                                event->name, event->position);

  struct discord_create_message params = {
      .embeds = &(struct discord_embeds){.size = 1, .array = &embed}};

  discord_create_message(client, channelID, &params, NULL);
  discord_embed_cleanup(&embed);
}
