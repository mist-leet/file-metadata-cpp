#include "file_structs.h"
using namespace std;

GeneralInfo::GeneralInfo()
{}

bool GeneralInfo::isEmpty() const
{
    return title.isEmpty() && titleSorting.isEmpty() && performer.isEmpty() &&
            performerSorting.isEmpty() && album.isEmpty() && albumSorting.isEmpty();
}

bool GeneralInfo::hasAllDisplayableData() const
{
    return !title.isEmpty() && !performer.isEmpty() && !album.isEmpty();
}

bool FileMetadata::hasInfo() const//нужно поддерживать в актуальном состоянии!
{
    return albumPosition.first || setPosition.first || !textFields.isEmpty() ||
            !commercial.isEmpty() || !ufids.isEmpty() || isrc[12] || !languages.isEmpty() || !generalInfo.isEmpty()
            ;
}

FileMetadata::FileMetadata()
{
    isrc[12] = 0;
}

bool FileMetadata::needsV1() const//неизвестно хотя бы что то из нижеперечисленного
{
    return !generalInfo.hasAllDisplayableData() || !textFields.contains("Comment") || !textFields.contains("Release time") ||
            !textFields.contains("Genre") || !albumPosition.first;
}
