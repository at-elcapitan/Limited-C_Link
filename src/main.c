/**
 * AT_C/LINK (c) by alice
 * 
 * AT_C/LINK is licensed under a
 * Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * 
 * You should have received a copy of the license along with this
 * work. If not, see <http://creativecommons.org/licenses/by-nc-nd/4.0/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <concord/discord.h>
#include <concord/log.h>

void onReady(struct discord *client, const struct discord_ready *event) {
    log_info("Bot started. Setting up presence");

    struct discord_activity activities[] = {
        {
            .name = "Link, start..",
            .type = DISCORD_ACTIVITY_GAME,
            .details = "Enhance Armament"
        },
    };

    struct discord_presence_update status = {
        .activities = 
            &(struct discord_activities) {
                .size = sizeof(activities) / sizeof *activities,
                .array = activities,
        },
        .status = "Rading system call command",
        .afk = false,
        .since = discord_timestamp(client),
    };

    discord_update_presence(client, &status);
}

int main(int argc, char const *argv[])
{   
    printf("(c) Vladislav 'ElCapitan' Nazarov\n");
    printf("AT PROJECT Limited, 2022 - 2023; AT_C/LINK-setup\n");
    printf("Product licensed by CC BY-NC-ND-4, file `LICENSE`\n");
    printf("The license applies to all project files and previous versions (commits)\n\n");

    log_info("Stage: starting");
    struct discord *client = discord_config_init("config.json");
    discord_add_intents(client, DISCORD_GATEWAY_MESSAGE_CONTENT);
    discord_set_on_ready(client, &onReady);
    discord_run(client);

    return 0;
}
