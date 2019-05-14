# (c) 2019, Iakov Kirilenko

FROM ubuntu:16.04
ENV DEBIAN_FRONTEND noninteractive
RUN useradd -M -d /sandbox sandbox
RUN apt-get -y update \
    && apt-get -y install libstdc++6 xterm libegl1-mesa libxkbcommon-x11-0 libpulse-mainloop-glib0 \
    && apt-get -y update \
    && apt-get -y dist-upgrade

#HOTFIX: alsa device 0 was incorrect
RUN echo "pcm.!default hw:PCH" > /root/.asoundrc
ADD trik-studio-offline-linux-gnu64-installer /
#RUN ldd /trik-studio-offline-linux-gnu64-installer --help
