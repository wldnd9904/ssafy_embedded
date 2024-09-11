CC = gcc
CFLAGS = -O2 -w
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

# 기본 타겟
all: ssshell

# 링크 타겟
ssshell: $(OBJS)
	$(CC) -o $@ $^

# 패턴 규칙
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# 클린업 타겟
clean:
	rm -f $(OBJS) ssshell

