/************************************************************************
Copyright 2019, Jose de Leon (a.k.a: Christian on FICS at freechess.org)

This file is part of Sjakk

Sjakk is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Sjakk is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Sjakk.  If not, see <https://www.gnu.org/licenses/>.
************************************************************************/

#include "timeseal.h"

/*!
 *
 * \mainpage
 *
 * \section intro_sec Introduction
 *
 * Timeseal is a protocol utilized by the Free Internet Chess Server, a.k.a. FICS.  The Timeseal protocol
 * calculates the network delay inherent in sending chess moves between the server and the client (player) and
 * then adds time back to the player clocks to compensate for what is commonly referred to as 'lag' by FICS players.
 *
 * There are two versions of the protocol. Timeseal 1 is the original version, Timeseal 2 has better detection of
 * network lag.
 *
 * QtTimeseal implements Timeseal 2 protocol and is cross-platform compatible. Loosely derived from Zseal by Felipe Bergo,
 * repository at https://github.com/fbergo/zseal.
 *
 * \section package_sec What is Included
 *
 * - Timeseal class for use in your programs
 * - GUI Test Harness using QWidget
 *
 *   This is a working example that connects to FICS and you can use it to play a game
 *   the old fashioned way before there were GUI based chess clients.  BONUS, provides example for using Timeseal
 *
 * - Console Test Harness for command line usage
 *
 *   Also a working example, but works from command line only and can use to play games as well.  BONUS, provides example
 *   for using Timeseal.  DOUBLE BONUS, you can use this as external timeseal component for your programs, simply hook up
 *   STDIN and STDOUT to your program.
 *
 */


/*!
 * \class Timeseal
 * \brief The Timeseal class
 *
 * The Timeseal class supports the FICS chess server timeseal v2 protocol.
 * To use in your application, do the following:
 *
 * - Your application must handle all socket communication with FICS chess server
 * - Upon successful connect to FICS, stamp() the returned value from hello() and write the QByteArray to the socket
 * - Handle all ping_echo() signals
 *     + stamp() the parameter from ping_echo()
 *     + Write the stamped QByteArray to the socket
 * - For all data received from FICS, send to process()
 *
 * Timeseal class makes basic assumptions about your socket reader/writer:
 *
 * 1. All data is read and written in raw, that is, you should be able to send and receive \000 (null) chars
 * 2. Your socket reader properly handles data that overflows your read buffer
 * 3. Your socket reader does not discard split server pings.  A server ping is a sequence of four
 * characters defined like:
 *
 *     QByteArray("[G]\0",4)
 *
 *    For example, on the first read of the socket buffer, the data consists of QByteArray("some text[G").
 *    Then on the second read, the rest of the ping is received QByteArray("]\0other data")
 *
 *
 * \sa TestHarness-Gui, TesteHarness-Console
 *
 */

void Timeseal::xor_swap(QByteArray &buffer, int a, int b)
    {
    buffer[a] = buffer[a] ^ buffer[b];
    buffer[b] = buffer[b] ^ buffer[a] ;
    buffer[a] = buffer[a] ^ buffer[b];
    }

Timeseal::Timeseal(QObject *parent) : QObject(parent)
    {
    }

QByteArray Timeseal::hello()
    {
    QString machine_str = QString("%1 %2 %3 %4 %5")
                          .arg(QSysInfo::productType().toUpper())
                          .arg(QSysInfo::machineHostName())
                          .arg(QSysInfo::kernelType())
                          .arg(QSysInfo::kernelVersion())
                          .arg(QSysInfo::currentCpuArchitecture());
    QString hello = QString("TIMESEAL2|qtTimesealUser (%1)|%2|").arg(version.data()).arg(machine_str);
    return QByteArray().append(hello);
    }

QByteArray Timeseal::stamp(QByteArray &buffer)
    {
    QByteArray encode_buffer(buffer);
    qint64 epoch_milliseconds = QDateTime::currentMSecsSinceEpoch();
    qint64 tsvalue;
    encode_buffer.append('\x18');
    tsvalue = epoch_milliseconds % 10000000;
    encode_buffer.append(QString::number(tsvalue));
    encode_buffer.append('\x19');
    int len = encode_buffer.size();

    while ((len % 12) != 0)
        {
        len++;
        encode_buffer.append('1');
        }

    len = encode_buffer.size();

    for (int n = 0; n < len; n += 12)
        {
        xor_swap(encode_buffer, n + 0, n + 11);
        xor_swap(encode_buffer, n + 2, n + 9);
        xor_swap(encode_buffer, n + 4, n + 7);
        }

    for (int n = 0; n < encode_buffer.size(); n++)
        encode_buffer[n] = ((encode_buffer[n] | '\x80') ^ timeseal_key[n % 50]) - 32;

    encode_buffer.append('\x80');
    encode_buffer.append('\x0a');
    return encode_buffer;
    }

void Timeseal::process(QByteArray &buffer)
    {
    int i = buffer.indexOf(ping);

    while (i != -1)
        {
        buffer.remove(i, ping.length());
        emit ping_echo(pong);
        i = buffer.indexOf(ping);
        }
    }
