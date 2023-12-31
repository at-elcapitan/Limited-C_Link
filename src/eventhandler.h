// AT_C/LINK (c) by Vladislav 'ElCapitan' Nazarov
//
// AT_C/LINK is licensed under a
// Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International
// License.
//
// You should have received a copy of the license along with this
// work. If not, see <http://creativecommons.org/licenses/by-nc-nd/4.0/>.

#pragma once
#include <concord/discord.h>
#include <concord/log.h>
#include <glib-2.0/glib.h>
#include <jansson.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void on_channel_update(struct discord *client,
                       const struct discord_channel *event);
void on_voice_state_update(struct discord *client,
                           const struct discord_voice_state *event);
void on_message_update(struct discord *client,
                       const struct discord_message *event);
void on_message_delete(struct discord *client,
                       const struct discord_message_delete *event);
void on_channel_create(struct discord *client,
                       const struct discord_channel *event);
void on_channel_delete(struct discord *client,
                       const struct discord_channel *event);
void events_init();
