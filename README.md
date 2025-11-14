# MTU Implementation in C

Path MTU Discovery implementation for bachelor's degree networking course.

## What is MTU?

Maximum Transmission Unit - the largest packet size that can be transmitted without fragmentation. Standard Ethernet MTU is 1500 bytes.

## Build

```bash
make
# or
gcc -o mtu src/*.c -I include -Wall
```

## Usage

```bash
sudo ./mtu 
```

Requires root for raw socket operations.

## Implementation

- Path MTU Discovery using ICMP echo requests
- Binary search algorithm to find optimal MTU
- Raw socket programming in C
- Don't Fragment (DF) bit handling

## References

- [RFC 1191 - Path MTU Discovery](https://tools.ietf.org/html/rfc1191)
- Stevens, "TCP/IP Illustrated, Vol. 1"

## Author

Salvatore Fadda  
Bachelor's Degree Project
