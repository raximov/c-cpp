
make            # builds into build/
make install    # installs to ~/3DViewer_v2.1_app/
make uninstall
make clean
make tests      # runs unit tests (requires libgtest-dev)
make dist       # creates tarball

LD_PRELOAD=/lib/x86_64-linux-gnu/libpthread.so.0 ./3DViewer
