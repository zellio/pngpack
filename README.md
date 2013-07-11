
# pngpack

Small utility for packing arbitrary files into PNG comment sections.

The files are stored as encrypted gziped binary blobs.

Currently encryption / decryption assumes there is a file called pngpack.key in
the root of the project which contains a 256 bit base64 encoded AES key without
a trailing newline.


## Copyright

Copyright (c) 2013 Zachary Elliott.
See LICENSE for further details.
