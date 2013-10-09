/*
  * Copyright (C) 2011 Cameron White
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef FORMATS_GUITARPROIMPORTER_H
#define FORMATS_GUITARPROIMPORTER_H

#include <formats/fileformat.h>
#include <formats/scorearranger.h>
#include "gp_fileformat.h"
#include <map>
#include <vector>

namespace Gp
{
class InputStream;
class Channel;
}

class ScoreInfo;

/// Imports Guitar Pro files.
class GuitarProImporter : public FileFormatImporter
{
public:
    GuitarProImporter();

    virtual void load(const std::string &filename, Score &score) override;

private:
    void findFileVersion(Gp::InputStream &stream);
    void readHeader(Gp::InputStream &stream, ScoreInfo &info);
#if 0

    std::vector<Gp::Channel> readChannels(Gp::InputStream &stream);

    void readColor(Gp::InputStream &stream);

    void readBarlines(Gp::InputStream &stream, uint32_t numMeasures,
                      std::vector<BarData> &bars);

    void readTracks(Gp::InputStream &stream, Score *score, uint32_t numTracks,
                    const std::vector<Gp::Channel> &channels);

    uint8_t convertKeyAccidentals(int8_t gpKey);

    Tuning readTuning(Gp::InputStream &stream);

    void readSystems(Gp::InputStream &stream, Score *score,
                     std::vector<BarData> bars);

    PositionData readBeat(Gp::InputStream &stream, const Tuning &tuning);

    uint8_t readDuration(Gp::InputStream &stream);

    void readRehearsalSign(Gp::InputStream &stream, RehearsalSign &sign);

    void readNotes(Gp::InputStream &stream, Position &position);

    void readNoteEffects(Gp::InputStream &stream, Position &position,
                         Note &note);
    void readNoteEffectsGp3(Gp::InputStream &stream, Position &position,
                            Note &note);

    void readSlide(Gp::InputStream &stream, Note &note);
    void readHarmonic(Gp::InputStream &stream, Note &note);
    void readBend(Gp::InputStream &stream, Note &note);
    void readTremoloBar(Gp::InputStream &stream, Position &position);
    void readMixTableChangeEvent(Gp::InputStream &stream,
                                 PositionData &position);
    void readPositionEffects(Gp::InputStream &stream, Position &position);

    void readChordDiagram(Gp::InputStream &stream, const Tuning &tuning);
    void readOldStyleChord(Gp::InputStream &stream, const Tuning &tuning);

    void readStartTempo(Gp::InputStream &stream, Score *score);

    static uint8_t convertTremoloEventType(uint8_t gpEventType);
    static uint8_t convertBendPitch(int32_t gpBendPitch);
#endif

    /// Supported version strings for Guitar Pro files (maps version strings to
    /// version number)
    static const std::map<std::string, Gp::Version> versionStrings;
};

#endif
