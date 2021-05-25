<h1 align="center">
  <img src="https://discord.com/assets/ff41b628a47ef3141164bfedb04fb220.png" alt="Discord">
</h1>

<p align="center"><b>This is the snap for Discord</b>, <i>"Discord is the easiest way to communicate over voice, video, and text. Chat, hang out, and stay close with your friends and communities."</i>. It works on Ubuntu, Fedora, Debian, and other major Linux distributions.</p>
<p align="center">
<a href="https://snapcraft.io/discord"><img src="https://snapcraft.io/discord/badge.svg" alt="Snap Status"></a>
</p>

## Install

    sudo snap install discord
    sudo snap connect discord:camera core:camera
    sudo snap connect discord:mount-observe core:mount-observe
    sudo snap connect discord:network-observe core:network-observe
    sudo snap connect discord:process-control core:process-control
    sudo snap connect discord:removable-media
    sudo snap connect discord:system-observe core:system-observe

([Don't have snapd installed?](https://snapcraft.io/docs/core/install))

![Discord](screenshot.png?raw=true "Discord")

<p align="center">Published for <img src="http://anything.codes/slack-emoji-for-techies/emoji/tux.png" align="top" width="24" /> with :gift_heart: by Snapcrafters</p>

## Remaining tasks

Snapcrafters ([join us](https://forum.snapcraft.io/t/join-snapcrafters/1325)) are working to land snap install documentation and the [snapcraft.yaml](https://github.com/snapcrafters/discord/blob/master/snap/snapcraft.yaml) upstream so Discord can authoritatively publish future releases.

  - [x] Fork the [Snapcrafters template](https://github.com/snapcrafters/fork-and-rename-me) repository to your own GitHub account
  - [x] Rename the forked Snapcrafters template repository
  - [x] Update logos and references to `[Project]` and `[my-snap-name]`
  - [x] Create a snap that runs in `devmode`
  - [x] Register the snap in the store, **using the preferred upstream name**
  - [x] Add a screenshot to this `README.md`
  - [x] Publish the `devmode` snap in the Snap store edge channel
  - [x] Add install instructions to this `README.md`
  - [x] Update snap store metadata, icons and screenshots
  - [x] Convert the snap to `strict` confinement, or `classic` confinement if it qualifies
  - [x] Publish the confined snap in the Snap store beta channel
  - [x] Update the install instructions in this `README.md`
  - [ ] Post a call for testing on the [Snapcraft Forum](https://forum.snapcraft.io) - [link]()
  - [x] Request your GitHub repository is forked to the Snapcrafters organisation and configured for automated builds
  - [x] Add the provided Snapcraft build badge to this `README.md`
  - [x] Publish the snap in the Snap store stable channel
  - [x] Update the install instructions in this `README.md`
  - [ ] Post an announcement in the [Snapcraft Forum](https://forum.snapcraft.io) - [link]()
  - [ ] Submit a pull request or patch upstream that adds snap install documentation - *discussing with upstream*
  - [ ] Submit a pull request or patch upstream that adds the `snapcraft.yaml` and any required assets/launchers - *discussing with upstream*
  - [x] Add upstream contact information to the `README.md`
  - If upstream accept the PR:
    - [ ] Request upstream create a Snap store account
    - [ ] Contact the Snap Advocacy team to request the snap be transferred to upstream
  - [x] Ask the Snap Advocacy team to celebrate the snap - [link](https://insights.ubuntu.com/2017/05/04/discord-is-now-available-as-a-snap-for-ubuntu-and-other-distributions/)

If you have any questions, [post in the Snapcraft forum](https://forum.snapcraft.io).

## The Snapcrafters

| [![Martin Wimpress](http://gravatar.com/avatar/ce95823a37d9ffa2e65a31cc60a2c42a/?s=128)](https://github.com/flexiondotorg/) |
| :---: |
| [Martin Wimpress](https://github.com/flexiondotorg/) |

## Upstream

| [![Chris Marsh](http://gravatar.com/avatar/288010bc9def7b7a1c68f417583407e9?s=128)](https://github.com/crmarsh) |
| :---: |
| [Chris Marsh](https://github.com/crmarsh) |

