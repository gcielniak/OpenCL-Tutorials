FROM archlinux:latest

# variable for user username to use in the container
ARG user_name=archie

# variable for user password to use in the container
ARG user_password=archer

# creating basic gpu capable archlinux system
RUN pacman -Syyuu sudo nvidia git base-devel python python-pip pyalpm fish neovim --noconfirm

# creating user with the desired permissions (NOPASS required for pikaur stages)
RUN useradd -m -p $(openssl passwd -1 ${user_password}) ${user_name} && \
    echo "${user_name} ALL=(ALL) ALL" >> /etc/sudoers && \
    echo "${user_name} ALL=(ALL) NOPASSWD:/usr/bin/pacman" >> /etc/sudoers && \
    echo "exec fish" >> /root/.bashrc

# swapping to our newly created user
USER ${user_name}

# clone, build, and install pikaur
RUN mkdir -p /home/${user_name}/git && \
    cd /home/${user_name}/git && \
    git clone "https://github.com/actionless/pikaur" && \
    cd /home/${user_name}/git/pikaur && \
    makepkg -s --noconfirm && \
    echo "${user_password}" | sudo -S pacman -U *pkg.tar.xz --noconfirm

# swapping back to root to continue since we no longer desire to be a user for makepkg
USER root

# install more specific packages from community and AUR as needed
# RUN sudo -u ${user_name} pikaur -S --noconfirm grpc-git

# changing to final user in case interactivity is desired
USER ${user_name}

# set up to build tensorflow (so that while we are still fiddling we dont stress archlinux servers)
RUN echo "${user_password}" | sudo -S pacman -S wget cmake opencl-nvidia ocl-icd opencl-headers clinfo cuda gcc --noconfirm

RUN mkdir -p /home/${user_name}/git && \
    mkdir -p /home/${user_name}/opencl_tutorials && \
    echo "cd ~" >> /home/${user_name}/.bashrc && \
    echo "exec fish" >> /home/${user_name}/.bashrc && \
    clinfo

COPY --chown=${user_name}:${user_name} ./* /home/${user_name}/opencl_tutorials/
