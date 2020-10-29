

#include <desktop_client/checker_mxf_file.hpp>

#include <mxf_specific_parameters_lib/MxfInfo.hpp>

/*
 *
{
    "FormatVersion": {
        "ExpectedValue": "1.1"
    },
    "IndexTableValues": {
        "Slice count": {
            "CompareRules": {
                "ComparatorMain": {
                    "Operator": "=",
                    "Value": 0
                }
            }
        }
    },
    "RIPPresence": {
        "ExpectedValue": true
    },
    "Resolution": {
        "Stored Resolution": {
            "H": {
                "ExpectedValue": 0
            },
            "W": {
                "ExpectedValue": 0
            }
        }
    },
    "VideoLineMap": {
        "Field1": {
            "ExpectedValue": 0
        },
        "Field2": {
            "ExpectedValue": 0
        }
    }
}
 */

#include <string>

// common code
template<typename Enum>
struct EnableBitMaskOperators
{
    static const bool enable = false;
};

template<typename Enum>
typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type
operator |(Enum lhs, Enum rhs)
{
    using underlying = typename std::underlying_type<Enum>::type;
    return static_cast<Enum> (
            static_cast<underlying>(lhs) |
            static_cast<underlying>(rhs)
    );
}


#define ENABLE_BITMASK_OPERATORS(x)  \
template<>                           \
struct EnableBitMaskOperators<x>     \
{                                    \
    static const bool enable = true; \
};


enum class OpsCompare : uint8_t
{
    None =      0x00u,  // 0
    Equal =     0x01u,  // =
    Greater =   0x02u,  // >
    Less =      0x04u,  // <
    Not =       0x08u,  // !
    NotEqual =       Not | Equal,      // !=
    GreaterOrEqual = Greater | Equal,  // >=
    LessOrEqual =    Less | Equal      // <=
};
ENABLE_BITMASK_OPERATORS(OpsCompare)


OpsCompare sym_to_ops_compare(int8_t symbol)
{
    switch (symbol) {
        case ('='):{
            return OpsCompare::Equal;
        } break;
        case ('>'):{
            return OpsCompare::Greater;
        } break;
        case ('<'):{
            return OpsCompare::Less;
        } break;
        case ('!'):{
            return OpsCompare::Not;
        } break;
        default:{
            return OpsCompare::None;
        }
    }
}


class Comparator
{
public:
    Comparator()
            : m_opCompare{OpsCompare::None}
    {}

    explicit Comparator(OpsCompare op)
            : m_opCompare{op}
    {}

    ~Comparator() = default;

    bool empty() const { return m_opCompare == OpsCompare::None; }

    bool compare(int64_t left, int64_t right) const
    {
        switch (m_opCompare) {
            case (OpsCompare::Equal):{
                return left == right;
            }
            case (OpsCompare::NotEqual):{
                return left != right;
            }
            case (OpsCompare::Greater):{
                return left > right;
            }
            case (OpsCompare::Less):{
                return left < right;
            }
            case (OpsCompare::GreaterOrEqual):{
                return left >= right;
            }
            case (OpsCompare::LessOrEqual):{
                return left <= right;
            }
            default:{
                return false;
            }
        }
    }

    std::string str() const {
        thread_local static std::map<OpsCompare, std::string> dict {
                {OpsCompare::None, "None"},
                {OpsCompare::Equal, "Equal"},
                {OpsCompare::NotEqual, "Not Equal"},
                {OpsCompare::Greater, "Greater"},
                {OpsCompare::Less, "Less"},
                {OpsCompare::GreaterOrEqual, "Greater or equal"},
                {OpsCompare::LessOrEqual, "Less or equal"}
        };
        const auto found = dict.find(m_opCompare);
        if (found != dict.end()){
            return found->second;
        }
        return "";
    }

    static Comparator from_string(const std::string & str){
        OpsCompare op_comp1 = sym_to_ops_compare(str.at(0));
        OpsCompare op_comp2 = OpsCompare::None;
        if (str.size() > 1){
            op_comp2 = sym_to_ops_compare(str.at(1));
        }
        const auto res_op_comp = op_comp1 | op_comp2;
        return Comparator{ res_op_comp };
    }

private:
    OpsCompare m_opCompare;

};


// checker functions

void check_format_version(mxf_info::MxfInfo &mxf_info, std::stringstream &ss, const QJsonObject &obj)
{
    const auto expected_value = obj["ExpectedValue"].toString().toStdString();
    const auto actual_value = mxf_info.getFormatVersion();
    const auto is_equal = (expected_value == actual_value);
    if (is_equal){
        ss << "SUCCESS" << std::endl;
        ss << "Actual: " << actual_value << " equal Expected: " << expected_value << std::endl;
    }
    else {
        ss << "FAILED" << std::endl;
        ss << "Actual: " << actual_value << " not equal Expected: " << expected_value << std::endl;
    }
}


void check_index_table_values(mxf_info::MxfInfo &mxf_info, std::stringstream &ss, const QJsonObject &obj)
{
    const auto actual_big_struct = mxf_info.getIndexTableValues();
    if (obj.contains("Duration")){
        const auto op_comp = obj["Duration"]["CompareRules"]["ComparatorMain"]["Operator"].toString().toStdString();
        const auto expected_dur = obj["Duration"]["CompareRules"]["ComparatorMain"]["Value"].toInt();
        const auto comparator = Comparator::from_string(op_comp);
        ss << "Duration" << std::endl;
        const auto actual_dur = actual_big_struct.m_duration;
        const auto is_equal = comparator.compare(actual_dur, expected_dur);
        if (is_equal){
            ss << "SUCCESS" << std::endl;
            ss << "Actual: " << actual_dur << " ["
               << comparator.str() << "] Expected: " << expected_dur << std::endl;
        }
        else {
            ss << "FAILED" << std::endl;
            ss << "Actual: " << actual_dur << " not rule: ["
               << comparator.str() << "] Expected: " << expected_dur << std::endl;
        }

    }
    if (obj.contains("Edit Unit Byte Count")){
        const auto op_comp = obj["Edit Unit Byte Count"]["CompareRules"]["ComparatorMain"]["Operator"].toString().toStdString();
        const auto expected_edit_unit_byte = obj["Edit Unit Byte Count"]["CompareRules"]["ComparatorMain"]["Value"].toInt();
        const auto comparator = Comparator::from_string(op_comp);
        ss << "Edit Unit Byte Count" << std::endl;
        const auto actual_edit_unit_byte = actual_big_struct.m_edit_unit_byte_count;
        const auto is_equal = comparator.compare(actual_edit_unit_byte, expected_edit_unit_byte);
        if (is_equal){
            ss << "SUCCESS" << std::endl;
            ss << "Actual: " << actual_edit_unit_byte << " ["
               << comparator.str() << "] Expected: " << expected_edit_unit_byte << std::endl;
        }
        else {
            ss << "FAILED" << std::endl;
            ss << "Actual: " << actual_edit_unit_byte << " not rule: ["
               << comparator.str() << "] Expected: " << expected_edit_unit_byte << std::endl;
        }
    }
    if (obj.contains("Position Table Count")){
        const auto op_comp = obj["Position Table Count"]["CompareRules"]["ComparatorMain"]["Operator"].toString().toStdString();
        const auto expected_position_table_count = obj["Position Table Count"]["CompareRules"]["ComparatorMain"]["Value"].toInt();
        const auto comparator = Comparator::from_string(op_comp);
        ss << "Position Table Count" << std::endl;
        const auto actual_position_table_count = actual_big_struct.m_position_table_count;
        const auto is_equal = comparator.compare(actual_position_table_count, expected_position_table_count);
        if (is_equal){
            ss << "SUCCESS" << std::endl;
            ss << "Actual: " << actual_position_table_count << " ["
               << comparator.str() << "] Expected: " << expected_position_table_count << std::endl;
        }
        else {
            ss << "FAILED" << std::endl;
            ss << "Actual: " << actual_position_table_count << " not rule: ["
               << comparator.str() << "] Expected: " << expected_position_table_count << std::endl;
        }
    }
    if (obj.contains("Slice count")){
        const auto op_comp = obj["Slice count"]["CompareRules"]["ComparatorMain"]["Operator"].toString().toStdString();
        const auto expected_slice_count = obj["Slice count"]["CompareRules"]["ComparatorMain"]["Value"].toInt();
        const auto comparator = Comparator::from_string(op_comp);
        ss << "Slice count" << std::endl;
        const auto actual_slice_count = actual_big_struct.m_slice_count;
        const auto is_equal = comparator.compare(actual_slice_count, expected_slice_count);
        if (is_equal){
            ss << "SUCCESS" << std::endl;
            ss << "Actual: " << actual_slice_count << " ["
               << comparator.str() << "] Expected: " << expected_slice_count << std::endl;
        }
        else {
            ss << "FAILED" << std::endl;
            ss << "Actual: " << actual_slice_count << " not rule: ["
               << comparator.str() << "] Expected: " << expected_slice_count << std::endl;
        }
    }

}


void check_rip_resence(mxf_info::MxfInfo &mxf_info, std::stringstream &ss, const QJsonObject &obj)
{
    const auto expected_value = obj["ExpectedValue"].toBool();
    const auto actual_value = mxf_info.getRIPPresence();
    const auto is_equal = expected_value == actual_value;
    if (is_equal){
        ss << "SUCCESS" << std::endl;
        ss << "Actual: " << std::boolalpha << actual_value
        << " equal Expected: " << std::boolalpha << expected_value << std::endl;
    }
    else {
        ss << "FAILED" << std::endl;
        ss << "Actual: " << std::boolalpha << actual_value
        << " not equal Expected: " << std::boolalpha << expected_value << std::endl;
    }

}

/*
"Resolution": {
        "Stored Resolution": {
            "H": {
                "ExpectedValue": 0
            },
            "W": {
                "ExpectedValue": 0
            }
        }
    }
 */
void check_resolution(mxf_info::MxfInfo &mxf_info, std::stringstream &ss, const QJsonObject &obj)
{
    const auto actual_big_struct = mxf_info.getResolution();

    if (obj.contains("Stored Resolution")){
        const auto actual_stored_h = actual_big_struct.stored_resolution().m_h;
        const auto actual_stored_w = actual_big_struct.stored_resolution().m_w;
        const auto expected_stored_h = obj["Stored Resolution"]["H"]["ExpectedValue"].toInt();
        const auto expected_stored_w = obj["Stored Resolution"]["W"]["ExpectedValue"].toInt();
        ss << "Stored Resolution" << std::endl;

        const auto is_equal = (
                actual_stored_h == expected_stored_h
                &&
                actual_stored_w == expected_stored_w);
        if (is_equal){
            ss << "SUCCESS" << std::endl;
            ss << "Actual: W:" << actual_stored_w << " H: " << actual_stored_h <<
            " equal Expected: W:" << expected_stored_w << " H: " << expected_stored_h << std::endl;
        }
        else {
            ss << "FAILED" << std::endl;
            ss << "Actual: W:" << actual_stored_w << " H: " << actual_stored_h <<
               " not equal Expected: W:" << expected_stored_w << " H: " << expected_stored_h << std::endl;
        }

    }
    if (obj.contains("Display Resolution")){
        const auto actual_display_h = actual_big_struct.display_resolution().m_h;
        const auto actual_display_w = actual_big_struct.display_resolution().m_w;
        const auto expected_display_h = obj["Display Resolution"]["H"]["ExpectedValue"].toInt();
        const auto expected_display_w = obj["Display Resolution"]["W"]["ExpectedValue"].toInt();
        ss << "Display Resolution" << std::endl;

        const auto is_equal = (
                actual_display_h == expected_display_h
                &&
                actual_display_w == expected_display_w);
        if (is_equal){
            ss << "SUCCESS" << std::endl;
            ss << "Actual: W:" << actual_display_w << " H: " << actual_display_h <<
               " equal Expected: W:" << expected_display_w << " H: " << expected_display_h << std::endl;
        }
        else {
            ss << "FAILED" << std::endl;
            ss << "Actual: W:" << actual_display_w << " H: " << actual_display_h <<
               " not equal Expected: W:" << expected_display_w << " H: " << expected_display_h << std::endl;
        }
    }
    if (obj.contains("Sampled Resolution")){
        const auto actual_sampled_h = actual_big_struct.sampled_resolution().m_h;
        const auto actual_sampled_w = actual_big_struct.sampled_resolution().m_w;
        const auto expected_sampled_h = obj["Sampled Resolution"]["H"]["ExpectedValue"].toInt();
        const auto expected_sampled_w = obj["Sampled Resolution"]["W"]["ExpectedValue"].toInt();
        ss << "Sampled Resolution" << std::endl;

        const auto is_equal = (
                actual_sampled_h == expected_sampled_h
                &&
                actual_sampled_w == expected_sampled_w);
        if (is_equal){
            ss << "SUCCESS" << std::endl;
            ss << "Actual: W:" << actual_sampled_w << " H: " << actual_sampled_h <<
               " equal Expected: W:" << expected_sampled_w << " H: " << expected_sampled_h << std::endl;
        }
        else {
            ss << "FAILED" << std::endl;
            ss << "Actual: W:" << actual_sampled_w << " H: " << actual_sampled_h <<
               " not equal Expected: W:" << expected_sampled_w << " H: " << expected_sampled_h << std::endl;
        }
    }

}

/*
    "VideoLineMap": {
        "Field1": {
            "ExpectedValue": 0
        },
        "Field2": {
            "ExpectedValue": 0
        }
    }
 */
void check_video_line_map(mxf_info::MxfInfo &mxf_info, std::stringstream &ss, const QJsonObject &obj)
{
    const auto actual_big_struct = mxf_info.getVideoLineMap();
    const auto actual_field1 = actual_big_struct.field1();
    const auto actual_field2 = actual_big_struct.field2();

    const auto expected_field1 = obj["Field1"]["ExpectedValue"].toInt();
    const auto expected_field2 = obj["Field2"]["ExpectedValue"].toInt();

    const auto is_equal = (
            actual_field1 == expected_field1
            &&
            actual_field2 == expected_field2
            );
    if (is_equal){
        ss << "SUCCESS" << std::endl;
        ss << "Actual: Field_1: " << actual_field1 << ", Field_2: " << actual_field2 <<
           " equal Expected Field_1: " << expected_field1 << ", Field_2: " << expected_field2 << std::endl;
    }
    else {
        ss << "FAILED" << std::endl;
        ss << "Actual: Field_1: " << actual_field1 << ", Field_2: " << actual_field2 <<
           " not equal Expected Field_1: " << expected_field1 << ", Field_2: " << expected_field2 << std::endl;
    }
}


void check_file_with_out(std::stringstream &ss, const QString &filePath, const QJsonObject &obj)
{
    mxf_info::MxfInfo mxf_info {filePath.toStdString()};

    if (obj.contains("FormatVersion")){
        ss << "-----FormatVersion-----" << std::endl;
        check_format_version(mxf_info, ss, obj["FormatVersion"].toObject());
        ss << "-----------------------" << std::endl;
    }
    if (obj.contains("IndexTableValues")){
        ss << "-----IndexTableValues-----" << std::endl;
        check_index_table_values(mxf_info, ss, obj["IndexTableValues"].toObject());
        ss << "-----------------------" << std::endl;
    }
    if (obj.contains("RIPPresence")){
        ss << "-----RIPPresence-----" << std::endl;
        check_rip_resence(mxf_info, ss, obj["RIPPresence"].toObject());
        ss << "-----------------------" << std::endl;
    }
    if (obj.contains("Resolution")){
        ss << "-----Resolution-----" << std::endl;
        check_resolution(mxf_info, ss, obj["Resolution"].toObject());
        ss << "-----------------------" << std::endl;
    }
    if (obj.contains("VideoLineMap")){
        ss << "-----VideoLineMap-----" << std::endl;
        check_video_line_map(mxf_info, ss, obj["VideoLineMap"].toObject());
        ss << "-----------------------" << std::endl;
    }

}
