#pragma once
#include <concord/discord.h>
#include <concord/log.h>

void on_message_bulk_delete(struct discord *client,
                            const struct discord_message *event);
