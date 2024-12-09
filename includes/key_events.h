/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 20:07:54 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/12/09 16:55:27 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEY_EVENTS_H
# define KEY_EVENTS_H

// content form orginal X.h
/* Input Event Masks. Used as event-mask window attribute and as arguments
   to Grab requests.  Not to be confused with event names.  */

// Input Event Masks
# define NOEVENTMASK 0
# define KEYPRESSMASK 1
# define KEYRELEASEMASK 2
# define BUTTONPRESSMASK 4
# define BUTTONRELEASEMASK 8
# define ENTERWINDOWMASK 16
# define LEAVEWINDOWMASK 32
# define POINTERMOTIONMASK 64
# define POINTERMOTIONHINTMASK 128
# define BUTTON1MOTIONMASK 256
# define BUTTON2MOTIONMASK 512
# define BUTTON3MOTIONMASK 1024
# define BUTTON4MOTIONMASK 2048
# define BUTTON5MOTIONMASK 4096
# define BUTTONMOTIONMASK 8192
# define KEYMAPSTATEMASK 16384
# define EXPOSUREMASK 32768
# define VISIBILITYCHANGEMASK 65536
# define STRUCTURENOTIFYMASK 131072
# define RESIZEREDIRECTMASK 262144
# define SUBSTRUCTURENOTIFYMASK 524288
# define SUBSTRUCTUREREDIRECTMASK 1048576
# define FOCUSCHANGEMASK 2097152
# define PROPERTYCHANGEMASK 4194304
# define COLORMAPCHANGEMASK 8388608
# define OWNERGRABBUTTONMASK 16777216

// Event names
# define KEYPRESS 2
# define KEYRELEASE 3
# define BUTTONPRESS 4
# define BUTTONRELEASE 5
# define MOTIONNOTIFY 6
# define ENTERNOTIFY 7
# define LEAVENOTIFY 8
# define FOCUSIN 9
# define FOCUSOUT 10
# define KEYMAPNOTIFY 11
# define EXPOSE 12
# define GRAPHICSEXPOSE 13
# define NOEXPOSE 14
# define VISIBILITYNOTIFY 15
# define CREATENOTIFY 16
# define DESTROYNOTIFY 17
# define UNMAPNOTIFY 18
# define MAPNOTIFY 19
# define MAPREQUEST 20
# define REPARENTNOTIFY 21
# define CONFIGURENOTIFY 22
# define CONFIGUREREQUEST 23
# define GRAVITYNOTIFY 24
# define RESIZEREQUEST 25
# define CIRCULATENOTIFY 26
# define CIRCULATEREQUEST 27
# define PROPERTYNOTIFY 28
# define SELECTIONCLEAR 29
# define SELECTIONREQUEST 30
# define SELECTIONNOTIFY 31
# define COLORMAPNOTIFY 32
# define CLIENTMESSAGE 33
# define MAPPINGNOTIFY 34
# define GENERICEVENT 35
# define LASTEVENT 36

#endif