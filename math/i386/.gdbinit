# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    .gdbinit                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abelov <abelov@student.42london.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/12 01:05:48 by abelov            #+#    #+#              #
#    Updated: 2025/03/12 01:05:49 by abelov           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

set confirm off
set pagination off
set height unlimited
#set verbose on
#set logging on
set trace-commands on
set print inferior-events on

set breakpoint pending on
set mem inaccessible-by-default off

br _start

tui enable
set tui border-mode reverse
list _start
#tui reg sse
tui reg float
