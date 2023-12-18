![Static Badge](https://img.shields.io/badge/Language-C-lightgrey) ![Static Badge](https://img.shields.io/badge/Library-Concord-purple)

## About

This bot is a part of `Limited` bots:
- [Limited nEXT](https://github.com/at-elcapitan/Limited_Py)
- [Limited C/Link](https://github.com/at-elcapitan/Limited-C_Link) (this)
- [Limited jEXT](https://github.com/at-elcapitan/AT-Limited_jEXT)

`C/Link` is a simple single-server logging bot made with the `Concord` discord API library.

## Installation

Before copying bot sources, install [Concord](https://github.com/Cogmasters/concord) library.

Then copy bot sources with
``` bash
git clone https://github.com/at-elcapitan/Limited-C_Link.git
```

Then run the command to compile sources
``` make ```

Bot executable will appear in `./out/`

## Configuring

Create a `logs` folder in the folder, where the bot's executable is placed.

Create a `config.json` file using the template (template from Concord [README.md](https://github.com/Cogmasters/concord#configuring-concord)):

```
{
  "logging": { // logging directives
    "level": "trace",        // trace, debug, info, warn, error, fatal
    "filename": "logs/bot.log",   // the log output file
    "quiet": false,          // change to true to disable logs in console
    "overwrite": true,       // overwrite file if already exists, append otherwise
    "use_color": true,       // display color for log entries
    "http": {
      "enable": true,        // generate http specific logging
      "filename": "logs/http.log" // the HTTP log output file
    },
    "disable_modules": ["WEBSOCKETS", "USER_AGENT"] // disable logging for these modules
  },
  "discord": { // discord directives
    "token": "YOUR-BOT-TOKEN",         // replace with your bot token
    "default_prefix": {                 
      "enable": false,                 // enable default command prefix
      "prefix": "YOUR-COMMANDS-PREFIX" // replace with your prefix
    }
  },
  "logging_channels" :
    {
      "1" : 1234567890123456789 // replace with your logging channel
    }
}
```

Create a `channels.json` file using the template:
```
{
  "ignorred_channels" : [ // Reaplce with your channel IDs
    "1234567890123456789", 
    ...
  ]
}
```

## Running

Run `bot` file
