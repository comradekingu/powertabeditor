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

#ifndef PAINTERS_SYSTEMRENDERER_H
#define PAINTERS_SYSTEMRENDERER_H

#include <painters/layoutinfo.h>
#include <painters/musicfont.h>
#include <score/staff.h>

class QGraphicsItem;
class QGraphicsRectItem;
class Score;
class ScoreArea;
class System;

class SystemRenderer
{
public:
    SystemRenderer(const ScoreArea *myScoreArea, const Score &myScore);
    
    QGraphicsItem *operator()(const System &system, int systemIndex,
                              Staff::ViewType view);

private:
    /// Draws the tab clef.
    void drawTabClef(double x, const LayoutInfo &layout);

    /// Draws barlines, along with time signatures, rehearsal signs, etc.
    void drawBarlines(const System &system, int systemIndex,
                      const LayoutConstPtr &layout, bool isFirstStaff);

    /// Draws the tab notes for all notes in the staff.
    void drawTabNotes(const Staff &staff, const LayoutConstPtr &layout);

    /// Centers an item, by using its width to calculate the necessary
    /// offset from xmin.
    void centerItem(QGraphicsItem *item, double xmin, double xmax, double y);

    /// Draws a arpeggio up/down at the given position.
    void drawArpeggio(const Position &position, double x,
                      const LayoutInfo &layout);

    /// Draws system-level symbols such as alternate endings and tempo markers.
    void drawSystemSymbols(const System &system, const LayoutInfo &layout);

    /// Draws a divider line between system symbols.
    void drawDividerLine(double y);

    /// Draws all of the alternate endings in the system.
    void drawAlternateEndings(const System &system, const LayoutInfo &layout,
                              double height);

    /// Draws all of the tempo markers in the system.
    void drawTempoMarkers(const System &system, const LayoutInfo &layout,
                          double height);

    /// Draws all of the directions in the system.
    double drawDirections(const System &system, const LayoutInfo &layout,
                        double height);

    /// Draws the text symbols that appear below the tab staff
    /// (hammerons, slides, etc).
    void drawSymbolsBelowTabStaff(const LayoutInfo &layout);

    /// Creates a pick stroke symbol using the given character.
    QGraphicsItem *createPickStroke(const QString &text);

    /// Creates a plain text item - useful for symbols that don't use the
    /// music font (hammerons, slides, etc).
    QGraphicsItem *createPlainTextSymbol(const QString &text,
                                         QFont::Style style);

    /// Draws symbols that appear above the standard notation staff (e.g. 8va).
    void drawSymbolsAboveStdNotationStaff(const LayoutInfo &layout);

    /// Draws symbols that are grouped across multiple positions
    /// (i.e. consecutive "let ring" symbols).
    QGraphicsItem *createConnectedSymbolGroup(const QString &text,
                                              QFont::Style style, double width,
                                              const LayoutInfo &layout);

    /// Draws symbols that appear below the standard notation staff (e.g. 8vb).
    void drawSymbolsBelowStdNotationStaff(const LayoutInfo &layout);

    /// Draws hammerons, pulloffs, etc in the tab staff.
    void drawLegato(const Staff &staff, const LayoutInfo &layout);

    /// Draws player changes for the given staff.
    void drawPlayerChanges(const System &system, int staffIndex,
                           const LayoutInfo &layout);

    /// Draws the symbols that appear above the tab staff (e.g. vibrato).
    void drawSymbolsAboveTabStaff(const Staff &staff, const LayoutInfo &layout);

    /// Draws a sequence of continuous music symbols (e.g. vibrato).
    QGraphicsItem *drawContinuousFontSymbols(QChar symbol, int width);

    /// Creates a tremolo picking symbol.
    QGraphicsItem *createTremoloPicking(const LayoutInfo &layout);

    /// Creates a trill symbol.
    QGraphicsItem *createTrill(const LayoutInfo &layout);

    /// Creates a dynamic symbol.
    QGraphicsItem *createDynamic(const Dynamic &dynamic);

    const ScoreArea *myScoreArea;
    const Score &myScore;

    QGraphicsRectItem *myParentSystem;
    QGraphicsItem *myParentStaff;

    MusicFont myMusicFont;
    QFont myMusicNotationFont;
    QFont myPlainTextFont;
    QFont mySymbolTextFont;
    QFont myRehearsalSignFont;

#if 0
    enum VolumeSwellType
    {
        VolumeIncreasing,
        VolumeDecreasing
    };

    void centerItem(QGraphicsItem* item, float xmin, float xmax, float y);

    void renderBars(const StaffData& currentStaffInfo);

    void drawTabNotes(const StaffData& currentStaffInfo);
    void drawArpeggio(const Position* position, uint32_t x, const StaffData& currentStaffInfo);

    void drawSystemSymbols(const StaffData& currentStaffInfo);
    void drawDividerLine(const StaffData& currentStaffInfo, quint32 y);
    void drawAltEndings(const std::vector<boost::shared_ptr<AlternateEnding> >& altEndings,
                        uint32_t height);
    void drawTempoMarkers(const std::vector<boost::shared_ptr<TempoMarker> >& tempoMarkers,
                          uint32_t height);
    void drawDirections(uint32_t height, const StaffData& currentStaffInfo);
    void drawChordText(uint32_t height, const StaffData& currentStaffInfo);

    void drawRhythmSlashes();

    void drawLegato(const StaffData& currentStaffInfo);
    void drawSlides(const StaffData& currentStaffInfo);
    void drawSlidesHelper(const StaffData& currentStaffInfo, quint8 string,
                          bool slideUp, int posIndex1, int posIndex2);

    void drawSymbolsBelowTabStaff(const StaffData& staffInfo);
    QGraphicsItem* createPickStroke(const QString& text);
    QGraphicsItem* createPlainText(const QString& text, QFont::Style style);
    QGraphicsItem* createArtificialHarmonicText(const Position* position);

    void drawSymbols(const StaffData& staffInfo);
    void drawSymbolsAboveStdNotationStaff(const StaffData &staffInfo);
    void drawSymbolsBelowStdNotationStaff(const StaffData &staffInfo);
    QGraphicsItem* createConnectedSymbolGroup(const QString& text, QFont::Style style, int width,
                                              const StaffData& currentStaffInfo);
    QGraphicsItem* createVolumeSwell(uint8_t width, const StaffData& currentStaffInfo,
                                     VolumeSwellType type);
    QGraphicsItem* drawContinuousFontSymbols(QChar symbol, int width);
    QGraphicsItem* createTremoloPicking(const StaffData& currentStaffInfo);
    QGraphicsItem* createTrill(const StaffData& currentStaffInfo);
    QGraphicsItem* createDynamic(boost::shared_ptr<const Dynamic> dynamic);
    QGraphicsItem* createBend(const Position* position, const StaffData& staffInfo);

    void drawStdNotation(const StaffData& currentStaffInfo);
    void adjustAccidentals(QMultiMap<int, StdNotationPainter*>& accidentalsMap);
    void drawMultiBarRest(boost::shared_ptr<const Barline> currentBarline,
                          const StaffData& currentStaffInfo, int measureCount);

    void drawLedgerLines(const std::vector<int> &noteLocations,
                         const double xLocation, const StaffData& staffData,
                         const double noteHeadWidth);
#endif
};

#endif
