#include "eventhandler.h"
#include "commands.h"

void on_voice_state_update(struct discord *client,
                           const struct discord_voice_state *event) {
  struct ccord_szbuf_readonly value;
  struct discord_embed embed = {.timestamp = discord_timestamp(client)};
  value =
      discord_config_get_field(client, (char *[2]){"logging_channels", "1"}, 2);
  u64snowflake channelID = strtol(value.start, NULL, 10);

  if (!event->channel_id) {
    embed.color = 0xFF0000;
    discord_embed_set_description(
        &embed, "<@%ld> **disconnected from the voice channel**",
        event->member->user->id);
  } else {
    embed.color = 0x7070C7;
    discord_embed_set_description(
        &embed, "<@%ld> **connected to the voice channel** <#%ld>",
        event->member->user->id, event->channel_id);
  }

  char desstring[5] = "";
  if (strcmp(event->member->user->discriminator, "0")) {
    sprintf(desstring, "#%s", event->member->user->discriminator);
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
  struct ccord_szbuf_readonly value;
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
