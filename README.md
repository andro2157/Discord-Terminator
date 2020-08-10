# Discord-Terminator

Automatically suspends the Discord account of the victim by setting the birthdate to 2015.

*This "attack" doesn't work for Discord accounts that have already set their birthdate
([Either with the prompt](https://www.reddit.com/r/discordapp/comments/gzwvcj/discord_asking_for_age_verification/) or during the registration time)*

The victims will then have 14 days to send to Discord a selfie containing their ID and their Discord Tag.
If they don't do so, their Discord account will be permanantly suspended.

## How does it work?

- When launched, this program will automatically grab the Discord token from the client's database using 2 methods:
  * Using [Google's LevelDB's library](https://github.com/google/leveldb/), which is the *proper* method.
  Although this method will most likely fail since the Discord client will lock the LevelDB database.
  * Using some ghetto parsing. This might parse old/invalid tokens even though it'll try to get the most recent one.
- Then if it was able to get the token, it'll send a PATCH request to Discord's API to update the user settings (the birthdate in this case).

### How to compile?

You'll need to build and include [Google's LevelDB's library](https://github.com/google/leveldb/) and [CURL](https://curl.haxx.se/dev/source.html).

I won't provide any pre-compiled build. *To avoid giving an easy access to scriptkiddies.*

## License

Discord-Terminator is under the GNU General Public License v3.0

### Please don't use this in malicious ways but for educational purposes
