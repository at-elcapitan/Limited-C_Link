/**
 * AT_C/LINK (c) by alice
 *
 * AT_C/LINK is licensed under a
 * Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International
 * License.
 *
 * You should have received a copy of the license along with this
 * work. If not, see <http://creativecommons.org/licenses/by-nc-nd/4.0/>.
 */

#include "main.h"

void onReady(struct discord *client, const struct discord_ready *event) {
  log_info("Bot started. Setting up presence");

  struct discord_activity activities[] = {
      {.name = "Link, start..",
       .type = DISCORD_ACTIVITY_GAME,
       .details = "Enhance Armament"},
  };

  struct discord_presence_update status = {
      .activities =
          &(struct discord_activities){
              .size = sizeof(activities) / sizeof *activities,
              .array = activities,
          },
      .status = "Rading system call command",
      .afk = false,
      .since = discord_timestamp(client),
  };

  discord_update_presence(client, &status);
  log_info("Ready.");
}

int main(int argc, char const *argv[]) {
  printf("(c) Vladislav 'ElCapitan' Nazarov\n");
  printf("AT PROJECT Limited, 2022 - 2023; AT_C/LINK-v0.0.2.1\n");
  printf("Product licensed by CC BY-NC-ND-4, file `LICENSE`\n");
  printf("The license applies to all project files and previous versions "
         "(commits)\n\n");

  log_info("Stage: starting");
  struct discord *client = discord_config_init("config.json");
  discord_add_intents(client, DISCORD_GATEWAY_MESSAGE_CONTENT);
  discord_add_intents(client, DISCORD_GATEWAY_DISPATCH);

  // Events
  discord_set_on_ready(client, &onReady);
  discord_set_on_voice_state_update(client, &on_voice_state_update);
  discord_set_on_message_update(client, &on_message_update);
  discord_set_on_message_delete(client, &on_message_delete);

  // Commands
  discord_set_on_command(client, "clear", &on_message_bulk_delete);

  discord_run(client);

  discord_cleanup(client);
  return 0;
}
