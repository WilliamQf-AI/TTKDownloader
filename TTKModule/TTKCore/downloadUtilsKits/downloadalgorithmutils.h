#ifndef DOWNLOADALGORITHMUTILS_H
#define DOWNLOADALGORITHMUTILS_H

/***************************************************************************
 * This file is part of the TTK Downloader project
 * Copyright (C) 2015 - 2025 Greedysky Studio

 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along
 * with this program; If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/

#include "ttkmoduleexport.h"

/*! @brief The namespace of the utils algorithm.
 * @author Greedysky <greedysky@163.com>
 */
namespace TTK
{
    namespace Algorithm
    {
        /*!
         * Get md5 algorithm.
         */
        TTK_MODULE_EXPORT QByteArray md5(const QByteArray &data);
        /*!
         * Get sha1 algorithm.
         */
        TTK_MODULE_EXPORT QByteArray sha1(const QByteArray &data);
        /*!
         * Encode the data into sha1.
         */
        TTK_MODULE_EXPORT QByteArray hmacSha1(const QByteArray &data, const QByteArray &key);

        /*!
         * Get mdII ttk algorithm.
         */
        TTK_MODULE_EXPORT QString mdII(const QString &data, bool encode);
        /*!
         * Get mdII ttk algorithm.
         */
        TTK_MODULE_EXPORT QString mdII(const QString &data, const char *key, bool encode);

    }
}

#endif // DOWNLOADALGORITHMUTILS_H
