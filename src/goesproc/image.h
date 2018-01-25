#pragma once

#include <memory>
#include <vector>

#include <opencv2/opencv.hpp>

#include "lrit/file.h"

class Image {
public:
  struct Region {
    std::string nameShort;
    std::string nameLong;
  };

  struct Channel {
    std::string nameShort;
    std::string nameLong;
  };

  static std::unique_ptr<Image> createFromFile(lrit::File file);

  explicit Image(lrit::File file);

  const lrit::File& getFile() const {
    return file_;
  }

  virtual std::string getSatellite() const;
  virtual Region getRegion() const;
  virtual Channel getChannel() const;
  virtual std::string getBasename() const;
  virtual struct timespec getTimeStamp() const;

  std::string getRegionShort() const {
    return getRegion().nameShort;
  }

  std::string getRegionLong() const {
    return getRegion().nameLong;
  }

  std::string getChannelShort() const {
    return getChannel().nameShort;
  }

  std::string getChannelLong() const {
    return getChannel().nameLong;
  }

  std::string getTimeShort() const;
  std::string getTimeLong() const;
  cv::Mat getRawImage() const;

protected:
  lrit::File file_;

  lrit::ImageStructureHeader is_;
  lrit::NOAALRITHeader nl_;
};

class ImageGOES13 : public Image {
public:
  explicit ImageGOES13(lrit::File file)
    : Image(file) {
  }

  virtual std::string getSatellite() const override;
  virtual Region getRegion() const override;
  virtual Channel getChannel() const override;
};

class ImageGOES15 : public Image {
public:
  explicit ImageGOES15(lrit::File file)
    : Image(file) {
  }

  virtual std::string getSatellite() const override;
  virtual Region getRegion() const override;
  virtual Channel getChannel() const override;
};

class ImageGOES16 : public Image {
public:
  explicit ImageGOES16(lrit::File file);

  virtual std::string getSatellite() const override;
  virtual Region getRegion() const override;
  virtual Channel getChannel() const override;
  virtual struct timespec getTimeStamp() const override;

protected:
  struct timespec frameStart_;
  std::string satellite_;
  std::string instrument_;
  Channel channel_;
  std::string imagingMode_;
  Region region_;
  std::string resolution_;
  bool segmented_;
};

class ImageHimawari8 : public Image {
public:
  explicit ImageHimawari8(lrit::File file)
    : Image(file) {
  }

  virtual std::string getSatellite() const override;
  virtual Region getRegion() const override;
  virtual Channel getChannel() const override;
  virtual struct timespec getTimeStamp() const override;
};

class ImageMeteosat : public Image {
public:
  explicit ImageMeteosat(lrit::File file)
    : Image(file) {
  }

  virtual std::string getSatellite() const override;
  virtual Region getRegion() const override;
  virtual Channel getChannel() const override;
};

class ImageNWS : public Image {
public:
  explicit ImageNWS(lrit::File file)
    : Image(file) {
  }

  virtual std::string getBasename() const override;
};
