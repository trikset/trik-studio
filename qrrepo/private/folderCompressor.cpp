/* Copyright 2007-2015 QReal Research Group
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License. */

#include "folderCompressor.h"

#include <QtCore/QDataStream>

#include "exceptions/corruptSavefileException.h"
#include "exceptions/couldNotCreateDestinationFolderException.h"
#include "exceptions/couldNotCreateOutFileException.h"
#include "exceptions/saveFileNotFoundException.h"
#include "exceptions/saveFileNotReadableException.h"
#include "exceptions/sourceFolderNotFoundException.h"
#include "exceptions/couldNotOpenDestinationFileException.h"
#include "exceptions/couldNotOpenInputFileException.h"

#ifdef TS_USE_SYSTEM_QUAZIP
#include "quazip5/JlCompress.h"
#else
#include "quazip/JlCompress.h"
#endif

using namespace qrRepo;
using namespace qrRepo::details;

void FolderCompressor::compressFolder(const QString &sourceFolder, const QString &destinationFile)
{
	if (!QDir(sourceFolder).exists()) {
		throw SourceFolderNotFoundException(sourceFolder);
	}

	if (!JlCompress::compressDir(destinationFile, sourceFolder, true, QDir::Filters())) {
		throw CouldNotCreateOutFileException(destinationFile);
	}
}

void FolderCompressor::decompressFolder(const QString &sourceFile, const QString &destinationFolder)
{
	if (!QFile(sourceFile).exists()) {
		throw SaveFileNotFoundException(sourceFile);
	}

	QDir dir;
	if (!dir.mkpath(destinationFolder)) {
		throw CouldNotCreateDestinationFolderException(destinationFolder);
	}

	if (!JlCompress::getFileList(sourceFile).isEmpty()) {
		if (JlCompress::extractDir(sourceFile, destinationFolder).isEmpty()) {
			throw SaveFileNotReadableException(sourceFile);
		}
	} else {
		decompressFolderOld(sourceFile, destinationFolder);
	}
}

void FolderCompressor::decompressFolderOld(const QString &sourceFile, const QString &destinationFolder)
{
	QDir dir;
	if (!dir.mkpath(destinationFolder)) {
		throw CouldNotCreateDestinationFolderException(destinationFolder);
	}

	QFile file(sourceFile);
	if (!file.open(QIODevice::ReadOnly)) {
		throw SaveFileNotReadableException(sourceFile);
	}

	QDataStream dataStream(&file);

	if (dataStream.atEnd()) {
		throw CorruptSaveFileException(sourceFile);
	}

	while (!dataStream.atEnd()) {
		QString fileName;
		QByteArray data;

		dataStream >> fileName >> data; // extract file name and data in order

		if (dataStream.status() != QDataStream::Ok) {
			// file is in wrong format, metadata is corrupt
			file.close();
			throw CorruptSaveFileException(sourceFile);
		}

		// create any needed folder
		for (int i = fileName.length() - 1; i > 0; --i) {
			if (QString(fileName.at(i)) == "\\" || QString(fileName.at(i)) == "/") {
				const QString subfolder = fileName.left(i);
				dir.mkpath(destinationFolder + "/" + subfolder);
				break;
			}
		}

		QFile outFile(destinationFolder + "/" + fileName);
		if (!outFile.open(QIODevice::WriteOnly)) {
			file.close();
			throw CouldNotCreateOutFileException(outFile.fileName());
		}

		const QByteArray uncompressedData = qUncompress(data);
		if (uncompressedData.isEmpty()) {
			file.close();
			throw CorruptSaveFileException(sourceFile);
		}

		outFile.write(uncompressedData);
		outFile.close();
	}

	file.close();
}

