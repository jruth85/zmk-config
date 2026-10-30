# Vial (QMK) backups

Layouts and firmware source for the QMK/Vial boards, kept here so a reflash
can't lose them.

- `corne/corne.vil`: the Corne layout. Load it in Vial with File > Load saved
  layout. Macros are left out of this public copy; keep the full file privately.
- `corne/keymap.c`: copy into `vial-qmk/keyboards/crkbd/keymaps/vial/`. The
  layout is compiled in as the default, so a wiped board boots into it.

Save a fresh .vil from Vial before every reflash.
