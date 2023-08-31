#include "eventhandler.h"

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
